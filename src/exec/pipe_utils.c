/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:56:12 by username          #+#    #+#             */
/*   Updated: 2024/12/27 04:29:04 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	clean_pipes(t_prompt *node, int pipefd[2])
{
	if (node->next_cmd)
	{
		close(pipefd[1]);
		if (node->next_cmd->in_fd != pipefd[0])
			close(pipefd[0]);
	}
	if (node->out_fd > 1)
		close(node->out_fd);
	if (node->in_fd > 0)
		close(node->in_fd);
}

void	ex_subprocess_pipes(int pipefd[2])
{
	if (pipefd[0] > 0)
		dup2(pipefd[0], STDIN_FILENO);
	if (pipefd[1] > 1)
		dup2(pipefd[1], STDOUT_FILENO);
	if (pipefd[1] > 1)
		close(pipefd[1]);
	if (pipefd[0] > 0)
		close(pipefd[0]);
}

void	std_pipe(t_prompt **node, int pipefd[2])
{
	if (node && *node)
	{
		(*node)->in_fd = pipefd[0];
		(*node)->out_fd = pipefd[1];
	}
	else if (node && !*node)
	{
		if (pipefd[0] > 0)
			close(pipefd[0]);
		if (pipefd[1] > 1)
			close(pipefd[1]);
	}
	pipefd[0] = STDIN_FILENO;
	pipefd[1] = STDOUT_FILENO;
}

void	close_pipe(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
}

void	close_unused_fd(t_ctx ctx)
{
	t_prompt	*curr;

	if (ctx.next_readpipe)
		close(ctx.next_readpipe);
	curr = ctx.node->next_cmd;
	while (curr)
	{
		if (curr->in_fd > 0 && curr->in_fd != ctx.next_readpipe)
			close(curr->in_fd);
		if (curr->out_fd > 1)
			close(curr->out_fd);
		curr = curr->next_cmd;
	}
}
