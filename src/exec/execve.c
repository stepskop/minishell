/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:34:17 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/19 23:32:28 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtins.h"
#include "path.h"

int	sh_run(char *cmmnd, t_ctx ctx)
{
	char	**cmmnds_args[3];
	int		pid;

	cmmnds_args[0] = sh_split_q (cmmnd, ';');
	ctx.to_free = cmmnds_args[0];
	free(cmmnd);
	cmmnds_args[1] = cmmnds_args[0];
	pid = 0;
	while (*cmmnds_args[1])
	{
		cmmnds_args[2] = sh_ud_rmbs (sh_split_q (*cmmnds_args[1], ' '));
		if (is_builtin(cmmnds_args[2][0]))
			pid = run_builtins(cmmnds_args[2], ctx);
		else
			pid = sh_execve (cmmnds_args[2], ctx);
		sh_ppfree (cmmnds_args[2]);
		cmmnds_args[1]++;
	}
	return (sh_ppfree (cmmnds_args[0]), pid);
}

void	sp_print_cnf(char *cmmnd)
{
	write (2, cmmnd, ft_strlen (cmmnd));
	write (2, ": command not found\n", 20);
}

int	ex_get_exitcode(t_prompt *node)
{
	int	status;

	if (node->proc_less)
		return (node->pid);
	waitpid(node->pid, &status, 0);
	//TODO: WHY THE FUCK THEY ARE TERMINATED BY SIGNAL
	if (WIFEXITED(status))
		printf("[%i] AWAITED STATUS: %i\n", node->pid, WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		printf("[%i] SIGNALED STATUS: %i\n", node->pid, WTERMSIG(status));
	return (status);
}

int	sh_execve(char **argv, t_ctx ctx)
{
	char	*cmmnd;
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		rl_clear_history ();
		cmmnd = path_resolve(argv[0]);
		ex_subprocess_pipes(ctx.pipefd);
		if (cmmnd)
			execve (cmmnd, argv, *ctx.penvp);
		else
			sp_print_cnf(argv[0]);
		run_exit (argv, ctx, NULL, EXIT_FAILURE);
		exit (EXIT_FAILURE);
	}
	ctx.node->pid = pid;
	return (pid);
}
