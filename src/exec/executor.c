/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:00:57 by username          #+#    #+#             */
/*   Updated: 2024/12/29 14:32:55 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "lexer.h"
#include "builtins.h"
#include "_malloc_.h"

static int	ex_handle_ionode(t_prompt *curr, int (*last_io)[2], char **envp)
{
	if ((curr->token == LESSLESS || curr->token == LESS) && (*last_io)[0] > 0)
		close((*last_io)[0]);
	else if ((curr->token == GREATGREAT || curr->token == GREAT) && \
		(*last_io)[1] > 1)
		close((*last_io)[1]);
	if (curr->token == LESSLESS)
		(*last_io)[0] = ex_get_heredoc(curr->args);
	else if (curr->token == LESS)
		(*last_io)[0] = ex_open_file(curr->args, O_RDONLY, envp);
	else if (curr->token == GREATGREAT)
		(*last_io)[1] = ex_open_file(curr->args,
				O_WRONLY | O_CREAT | O_APPEND, envp);
	else if (curr->token == GREAT)
		(*last_io)[1] = ex_open_file(curr->args,
				O_WRONLY | O_CREAT | O_TRUNC, envp);
	if (curr->token == GREATGREAT || curr->token == GREAT)
		curr->in_fd = (*last_io)[1];
	else if (curr->token == LESSLESS || curr->token == LESS)
		curr->out_fd = (*last_io)[0];
	if ((*last_io)[1] < 0 || (*last_io)[0] < 0)
		return (0);
	return (1);
}

static void	ex_ioprep(t_prompt *lst, char **envp)
{
	t_prompt	*curr;
	t_prompt	*l_cmd;
	int			last_io[2];

	curr = lst;
	l_cmd = NULL;
	std_pipe(NULL, last_io);
	while (curr)
	{
		if (curr->token == CMD)
			l_cmd = curr;
		if (!ex_handle_ionode(curr, &last_io, envp))
		{
			std_pipe(NULL, last_io);
			curr = curr->next;
			if (l_cmd)
				l_cmd->io_err = 1;
			continue ;
		}
		if (!curr->next || lx_cmdend(*(curr->next)))
			std_pipe(&l_cmd, last_io);
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
	res = _malloc_(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
		// return (perror("_malloc_"), NULL);
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

	std_pipe(NULL, c_pipe);
	std_pipe(NULL, pipefd);
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
	if (node->io_err)
		return (clean_pipes(node, pipefd),
			node->proc_less = 1, node->pid = 1, node);
	cmd = ex_cmdprep(node, penvp);
	sh_run(cmd, (t_ctx){c_pipe, pipefd[0], node, ast, NULL, penvp});
	clean_pipes(node, pipefd);
	return (node);
}

int	executor(t_prompt *lst, t_ast *ast, char ***penvp)
{
	t_prompt	*curr;
	int			stat;
	char		*status_var;

	ex_ioprep(lst, *penvp);
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
	if (!status_var)
		return (sh_err("Couldn't set last status env var\n"), stat);
	envp_set_var(penvp, status_var, 1);
	free(status_var);
	return (stat);
}
