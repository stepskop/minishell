/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:56:12 by username          #+#    #+#             */
/*   Updated: 2024/12/19 21:47:18 by username         ###   ########.fr       */
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

void	ex_processless_pipes(int pipefd[2], int std_backup[2])
{
	std_backup[0] = dup(STDIN_FILENO);
	std_backup[1] = dup(STDOUT_FILENO);
	if (pipefd[0] > 0)
		dup2(pipefd[0], STDIN_FILENO);
	if (pipefd[1] > 1)
		dup2(pipefd[1], STDOUT_FILENO);
}

void	close_pipe(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
}

void	restore_stdfd(int pipefd[2])
{
	dup2(pipefd[0], STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close_pipe(pipefd);
}
