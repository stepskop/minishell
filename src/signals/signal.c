/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:51:45 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/25 18:36:15 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

// static void	sigact_ign(int sig, siginfo_t *info, void *context);
static void	sigact(int sig, siginfo_t *info, void *context);

/*
ISO C99 signals.
SIGINT		2	Interactive attention signal.
SIGILL		4	Illegal instruction.
SIGABRT		6	Abnormal termination.
SIGFPE		8	Erroneous arithmetic operation.
SIGSEGV		11	Invalid access to storage.
SIGTERM		15	Termination request.

Historical signals specified by POSIX.
SIGHUP		1	Hangup.
SIGQUIT		3	Quit.
SIGTRAP		5	Trace/breakpoint trap.
SIGKILL		9	Killed.
SIGPIPE		13	Broken pipe.
SIGALRM		14	Alarm clock.
*/

void	sig_init(void)
{
	struct sigaction	sig;
	struct sigaction	sig_ign;
	sigset_t			block_mask[2];
	int					checker;

	sigemptyset (&block_mask[0]);
	sigemptyset (&block_mask[1]);
	sigaddset (&block_mask[0], SIGINT);
	sigaddset (&block_mask[1], SIGQUIT);
	sig.sa_mask = block_mask[0];
	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = &sigact;
	sig_ign.sa_mask = block_mask[1];
	sig_ign.sa_handler = SIG_IGN;
	sig_ign.sa_flags = 0;
	checker = sigaction(SIGINT, &sig, 0);
	checker += sigaction(SIGQUIT, &sig_ign, 0);
	if (checker != 0)
		sh_err ("create sigactions ERROR!");
}

// static void	sigact_ign(int sig, siginfo_t *info, void *context)
// {
// 	(void)sig;
// 	(void)info;
// 	(void)context;
// 	// write (2, "(sa_sigaction)-> SIGQUIT\n", 25);
// }

static void	sigact(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGINT)
	{
		if (info->si_pid)
		{
			write (1, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line ();
			rl_redisplay ();
		}
	}
}
