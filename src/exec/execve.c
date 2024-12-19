/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:34:17 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/19 21:47:46 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtins.h"
#include "path.h"

static int	check_builtins(char *cmmnd);

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
		if (check_builtins (cmmnds_args[2][0]))
			pid = run_builtins(cmmnds_args[2], ctx);
		else
			pid = sh_execve (cmmnds_args[2], ctx);
		sh_ppfree (cmmnds_args[2]);
		cmmnds_args[1]++;
	}
	return (sh_ppfree (cmmnds_args[0]), pid);
}

static int	check_builtins(char *cmmnd)
{
	if (!ft_strcmp (cmmnd, "echo")
		|| !ft_strcmp (cmmnd, "env")
		|| !ft_strcmp (cmmnd, "pwd")
		|| !ft_strcmp (cmmnd, "export")
		|| !ft_strcmp (cmmnd, "unset")
		|| !ft_strcmp (cmmnd, "cd")
		|| !ft_strcmp (cmmnd, "exit"))
		return (1);
	return (0);
}

void	sp_print_cnf(char *cmmnd)
{
	write (2, cmmnd, ft_strlen (cmmnd));
	write (2, ": command not found\n", 20);
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
		run_exit (argv, ctx);
		exit (EXIT_FAILURE);
	}
	return (pid);
}
