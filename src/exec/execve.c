/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:34:17 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/19 13:30:53 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (check_builtins (cmmnds_args[2][0]) == 1)
			pid = run_builtins_01 (cmmnds_args[2], ctx);
		else if (check_builtins (cmmnds_args[2][0]) == 2)
			pid = run_builtins_02 (cmmnds_args[2], ctx);
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
		|| !ft_strcmp (cmmnd, "cd")
		|| !ft_strcmp (cmmnd, "pwd"))
		return (1);
	else if (!ft_strcmp (cmmnd, "export")
		|| !ft_strcmp (cmmnd, "unset")
		|| !ft_strcmp (cmmnd, "env")
		|| !ft_strcmp (cmmnd, "exit"))
		return (2);
	else
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
		cmmnd = get_cmd (argv[0]);
		sh_subprocess_pipes(ctx.pipefd);
		if (cmmnd)
			execve (cmmnd, argv, sh_get_pv()->envp);
		else
			sp_print_cnf(argv[0]);
		sh_ppfree (argv);
		exit (EXIT_FAILURE);
	}
	return (pid);
}
