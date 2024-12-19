/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:49:36 by username          #+#    #+#             */
/*   Updated: 2024/12/19 17:38:37 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_subprocess_pipes(int pipefd[2])
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
