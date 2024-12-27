/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 03:51:55 by username          #+#    #+#             */
/*   Updated: 2024/12/27 03:53:55 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	restore_stdfd(int pipefd[2])
{
	dup2(pipefd[0], STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
}

void	processless_pipes(int pipefd[2], int std_backup[2])
{
	std_backup[0] = dup(STDIN_FILENO);
	std_backup[1] = dup(STDOUT_FILENO);
	if (pipefd[0] > 0)
		dup2(pipefd[0], STDIN_FILENO);
	if (pipefd[1] > 1)
		dup2(pipefd[1], STDOUT_FILENO);
}
