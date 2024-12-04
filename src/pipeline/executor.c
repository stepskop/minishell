/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:00:57 by username          #+#    #+#             */
/*   Updated: 2024/12/04 21:16:25 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ex_handle_ionode(t_prompt *curr, int (*last_io)[2])
{
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

void	executor(t_prompt *lst)
{
	//t_prompt	*curr;

	ex_ioprep(lst);
	print_lex_dbg(lst);
	//curr = lst;
	//while (curr)
	//{

	//	curr = curr->next;
	//}
}
