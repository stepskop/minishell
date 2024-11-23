/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:34:17 by ksorokol          #+#    #+#             */
/*   Updated: 2024/11/23 15:53:10 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sh_run(char *cmmnd)
{
	char	**cmmnds_args[3];
	int		rp;
	pid_t	pid;

	cmmnds_args[0] = sh_semicolon (cmmnd);
	cmmnds_args[1] = cmmnds_args[0];
	while (*cmmnds_args[1])
	{
		cmmnds_args[2] = sh_app_args (*cmmnds_args[1]);
		pid = fork ();
		if (pid == 0)
		{
			rl_clear_history ();
			free (cmmnd);
			sh_ppfree (cmmnds_args[0]);
			if (sh_execve (cmmnds_args[2], NULL) == -1)
				sp_print_cnf (cmmnds_args[2][0]);
			sh_ppfree (cmmnds_args[2]);
			exit (EXIT_SUCCESS);
		}
		sh_ppfree (cmmnds_args[2]);
		waitpid (pid, &rp, 0);
		cmmnds_args[1]++;
	}
	return (sh_ppfree (cmmnds_args[0]), EXIT_SUCCESS);
}

char	**sh_semicolon(char *cmmnd)
{
	return (ft_split (cmmnd, ';'));
}

char	**sh_app_args(char *cmmnd)
{
	return (ft_split (cmmnd, ' '));
}

void	sp_print_cnf(char *cmmnd)
{
	write (1, cmmnd, ft_strlen (cmmnd));
	write (1, ": command not found\n", 20);
}

int	sh_execve(char **argv, char **envp)
{
	char	*cmmnd;

	cmmnd = get_cmd (argv[0]);
	if (cmmnd)
		return (execve (cmmnd, argv, envp));
	return (-1);
}
