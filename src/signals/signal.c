/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:51:45 by ksorokol          #+#    #+#             */
/*   Updated: 2024/11/28 19:10:47 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_init(void)
{
	struct sigaction	sig;
	sigset_t			block_mask;
	int					checker;

	sigemptyset (&block_mask);
	sigaddset (&block_mask, SIGINT | SIGTERM | SIGCHLD);
	sig.sa_mask = block_mask;
	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = sigact;
	checker = sigaction(SIGINT, &sig, 0);
	checker += sigaction(SIGTERM, &sig, 0);
	checker += sigaction(SIGCHLD, &sig, 0);
	if (checker != 0)
		sh_err ("create sigactions ERROR!");
}

void	sigact(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGINT)
	{
		if (info->si_pid)
		{
			write (1, "\n", 1);
			rl_on_new_line ();
			rl_redisplay ();
		}
	}
	else if (sig == SIGTERM)
	{
		write (2, "(sa_sigaction)-> SIGTERM\n", 26);
	}
}
