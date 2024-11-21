/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:51:45 by ksorokol          #+#    #+#             */
/*   Updated: 2024/11/21 18:48:07 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_init(void)
{
	struct sigaction	sig;
	sigset_t			block_mask;
	int					checker;

	sigemptyset (&block_mask);
	sigaddset (&block_mask, 0b11111111 ^ (SIGINT | SIGTERM | SIGCHLD));
	// sigaddset (&block_mask, SIGINT | SIGTERM | SIGCHLD);
	sig.sa_mask = block_mask;
	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = sigact;
	sig.sa_handler = catcher;
	checker = sigaction(SIGINT, &sig, 0);
	checker += sigaction(SIGTERM, &sig, 0);
	checker += sigaction(SIGCHLD, &sig, 0);
	if (checker != 0)
		write (1, "create sigactions ERROR!\n", 25);
}

void	sigact(int sig, siginfo_t *info, void *context)
{
	(void)info->si_pid;
	(void)context;
	if (sig == SIGINT)
		write (1, "(sa_sigaction)-> SIGINT\n", 24);
	else if (sig == SIGTERM)
		write (1, "(sa_sigaction)-> SIGTERM\n", 25);
	else if (sig == SIGCHLD)
		write (1, "(sa_sigaction)-> SIGCHLD\n", 25);
}

void	catcher(int sig)
{
	if (sig == SIGINT)
		write (1, "(sa_handler)-> SIGINT\n", 22);
	else if (sig == SIGTERM)
		write (1, "(sa_handler)-> SIGTERM\n", 23);
	else if (sig == SIGCHLD)
		write (1, "(sa_handler)-> SIGCHLD\n", 23);
}
