/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:00:57 by username          #+#    #+#             */
/*   Updated: 2024/12/24 15:23:11 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "lexer.h"
#include "builtins.h"

static void	ex_handle_ionode(t_prompt *curr, int (*last_io)[2])
{
	if ((curr->token == LESSLESS || curr->token == LESS) && (*last_io)[0] > 0)
		close((*last_io)[0]);
	else if ((curr->token == GREATGREAT || curr->token == GREAT) && \
		(*last_io)[1] > 1)
		close((*last_io)[1]);
	if (curr->token == LESSLESS)
		(*last_io)[0] = ex_get_heredoc(curr->args);
	else if (curr->token == LESS)
		(*last_io)[0] = ex_open_file(curr->args, O_RDONLY);
	else if (curr->token == GREATGREAT)
		(*last_io)[1] = ex_open_file(curr->args, O_WRONLY | O_CREAT | O_APPEND);
	else if (curr->token == GREAT)
		(*last_io)[1] = ex_open_file(curr->args, O_WRONLY | O_CREAT | O_TRUNC);
	if (curr->token == GREATGREAT || curr->token == GREAT)
		curr->in_fd = (*last_io)[1];
	else if (curr->token == LESSLESS || curr->token == LESS)
		curr->out_fd = (*last_io)[0];
}

static void	ex_ioprep(t_prompt *lst)
{
	t_prompt	*curr;
	t_prompt	*last_cmd;
	int			last_io[2];

	curr = lst;
	last_io[0] = STDIN_FILENO;
	last_io[1] = STDOUT_FILENO;
	while (curr)
	{
		if (curr->token == CMD)
			last_cmd = curr;
		ex_handle_ionode(curr, &last_io);
		if (!curr->next || (curr->next && lx_cmdend(*(curr->next))))
		{
			last_cmd->in_fd = last_io[0];
			last_cmd->out_fd = last_io[1];
			last_io[0] = STDIN_FILENO;
			last_io[1] = STDOUT_FILENO;
		}
		curr = curr->next;
	}
}

static char	*ex_cmdprep(t_prompt *node, char ***penvp)
{
	char	*res;
	size_t	len;
	t_args	*curr;
	int		i;

	if (!ex_expand(node->args, *penvp))
		return (NULL);
	len = ex_cmdlen(node->args) + ft_strlen(node->str_val);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (perror("malloc"), NULL);
	i = ft_strlcpy(res, node->str_val, ft_strlen(node->str_val) + 1);
	curr = node->args;
	while (curr)
	{
		if (curr->data)
		{
			i += ft_strlcpy(res + i, " ", 2);
			i += ft_strlcpy(res + i, curr->data, ft_strlen(curr->data) + 1);
		}
		curr = curr->next;
	}
	return (res);
}

static t_prompt	*ex_execute(t_prompt *node, t_ast *ast, char ***penvp)
{
	int		pipefd[2];
	int		c_pipe[2];
	char	*cmd;

	c_pipe[0] = 0;
	c_pipe[1] = 1;
	if (node->next_cmd)
	{
		if (pipe(pipefd) == -1)
			return (perror("pipe"), NULL);
		c_pipe[1] = pipefd[1];
		if (node->next_cmd->in_fd == 0)
			node->next_cmd->in_fd = pipefd[0];
	}
	if (node->out_fd > 1)
		c_pipe[1] = node->out_fd;
	if (node->in_fd > 0)
		c_pipe[0] = node->in_fd;
	cmd = ex_cmdprep(node, penvp);
	sh_run(cmd, (t_ctx){c_pipe, node, ast, NULL, penvp});
	clean_pipes(node, pipefd);
	return (node);
}

int	executor(t_prompt *lst, t_ast *ast, char ***penvp)
{
	t_prompt	*curr;
	int			stat;
	char		*status_var;

	ex_ioprep(lst);
	curr = lst;
	stat = EXIT_SUCCESS;
	while (curr)
	{
		if (curr->token == CMD)
			ex_execute(curr, ast, penvp);
		curr = curr->next;
	}
	stat = ex_get_exitcode(lst);
	status_var = sh_strjoin_free("?=", ft_itoa(stat), 2);
	envp_set_var(penvp, status_var, 1);
	free(status_var);
	return (stat);
}
