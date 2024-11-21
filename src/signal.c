/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:51:45 by ksorokol          #+#    #+#             */
/*   Updated: 2024/11/20 23:01:50 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <stdio.h>

void	sig_init(void)
{
	struct sigaction	sig;
	sigset_t			block_mask;

	sigemptyset (&block_mask);
	sigaddset (&block_mask, 0b11111111 ^ (SIGINT));
	sig.sa_flags = SA_SIGINFO;
	sig.sa_mask = block_mask;
	sig.sa_sigaction = sigact;
	sigaction(SIGINT, &sig, 0);
}

void	sigact(int sig, siginfo_t *info, void *context)
{
	info->si_pid += 0;
	(void)context;
	if (sig == SIGINT)
		;
}
