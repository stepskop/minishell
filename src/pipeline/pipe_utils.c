/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:56:12 by username          #+#    #+#             */
/*   Updated: 2024/12/17 12:29:10 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"

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
