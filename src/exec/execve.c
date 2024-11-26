/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:34:17 by ksorokol          #+#    #+#             */
/*   Updated: 2024/11/26 18:05:26 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sh_run(char *cmmnd)
{
	char	**cmmnds_args[3];

	cmmnds_args[0] = sh_split_q (cmmnd, ';');
	cmmnds_args[1] = cmmnds_args[0];
	while (*cmmnds_args[1])
	{
		cmmnds_args[2] = sh_split_q (*cmmnds_args[1], ' ');
		if (!ft_strncmp (cmmnds_args[2][0], "echo", 4)
			|| !ft_strncmp (cmmnds_args[2][0], "cd", 2)
			|| !ft_strncmp (cmmnds_args[2][0], "pwd", 3)
			|| !ft_strncmp (cmmnds_args[2][0], "export", 6)
			|| !ft_strncmp (cmmnds_args[2][0], "unset", 5)
			|| !ft_strncmp (cmmnds_args[2][0], "env", 3)
			|| !ft_strncmp (cmmnds_args[2][0], "exit", 4))
			run_builtins (cmmnds_args[2]);
		else
			sh_execve (cmmnds_args[2], NULL, cmmnds_args[0], cmmnd);
		sh_ppfree (cmmnds_args[2]);
		cmmnds_args[1]++;
	}
	return (sh_ppfree (cmmnds_args[0]), EXIT_SUCCESS);
}

void	sp_print_cnf(char *cmmnd)
{
	write (1, cmmnd, ft_strlen (cmmnd));
	write (1, ": command not found\n", 20);
}

void	sh_execve(char **argv, char **envp, char **f_cmmnds, char *f_cmmnd)
{
	char	*cmmnd;
	pid_t	pid;
	int		rp;

	pid = fork ();
	if (pid == 0)
	{
		rl_clear_history ();
		sh_ppfree (f_cmmnds);
		free (f_cmmnd);
		rp = EXIT_SUCCESS;
		cmmnd = get_cmd (argv[0]);
		if (cmmnd)
			rp = execve (cmmnd, argv, envp);
		else
			sp_print_cnf (argv[0]);
		sh_ppfree (argv);
		exit (rp);
	}
	waitpid (pid, &rp, 0);
}
