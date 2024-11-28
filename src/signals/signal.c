/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:51:45 by ksorokol          #+#    #+#             */
/*   Updated: 2024/11/27 13:09:55 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_init(void)
{
	struct sigaction	sig;
	sigset_t			block_mask;
	int					checker;

	sigemptyset (&block_mask);
	// sigaddset (&block_mask, 0b11111111 ^ (SIGINT | SIGTERM | SIGCHLD));
	sigaddset (&block_mask, SIGINT | SIGTERM | SIGCHLD);
	sig.sa_mask = block_mask;
	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = sigact;
	checker = sigaction(SIGINT, &sig, 0);
	checker += sigaction(SIGTERM, &sig, 0);
	checker += sigaction(SIGCHLD, &sig, 0);
	if (checker != 0)
		write (1, "create sigactions ERROR!\n", 25);
}

void	sigact(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGINT)
	{
		// write (1, "\n(sa_sigaction)-> SIGINT\n", 25);
		if (info->si_pid)
		{
			write (1, "\n", 1);
			rl_on_new_line ();
			rl_redisplay ();
		}
	}
	else if (sig == SIGTERM)
	{
		write (1, "\n(sa_sigaction)-> SIGTERM\n", 26);
	}
}
