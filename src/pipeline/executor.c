/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:00:57 by username          #+#    #+#             */
/*   Updated: 2024/12/06 01:27:47 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	*ex_cmdprep(t_prompt *node)
{
	char	*res;
	size_t	len;
	char	*tmp;
	t_args	*curr;
	int		i;

	curr = node->args;
	while (curr)
	{
		tmp = curr->data;
		curr->data = put_env(curr->data);
		free(tmp);
		tmp = curr->data;
		curr->data = sh_asterisk(curr->data);
		free(tmp);
		curr = curr->next;
	}
	len = ex_cmdlen(node->args) + ft_strlen(node->str_val);
	res = malloc(sizeof(char) * (len + 1));
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

static int	ex_execute(t_prompt *node, char **envp)
{
	int		exit_code;
	int		pipefd[2];
	char	*cmd;

	if (node->in_fd > 0)
		dup2(node->in_fd, STDIN_FILENO);
	if (node->out_fd > 1)
		dup2(node->out_fd, STDOUT_FILENO);
	if (node->next_cmd && !node->next_cmd->in_fd)
	{
		if (pipe(pipefd) == -1)
			return (perror("pipe"), 1);
		dup2(pipefd[1], STDOUT_FILENO);
		node->next_cmd->in_fd = pipefd[0];
	}
	cmd = ex_cmdprep(node);
	(void)envp;
	//exit_code = sh_run(cmd, envp);
	printf("CMD: %s\n", cmd);
	exit_code = 0;
	if (node->next_cmd && !node->next_cmd->in_fd)
		close(pipefd[1]);
	return (exit_code);
}

void	executor(t_prompt *lst, char **envp)
{
	t_prompt	*curr;
	int			last_status;

	ex_ioprep(lst);
	print_lex_dbg(lst);
	curr = lst;
	last_status = 0;
	while (curr)
	{
		if (curr->token == CMD)
			last_status = ex_execute(curr, envp);
		if (curr->token == AND && last_status != 0)
			break ;
		if (curr->token == OR && last_status == 0)
			break ;
		curr = curr->next;
	}
}
