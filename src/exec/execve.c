/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:34:17 by ksorokol          #+#    #+#             */
/*   Updated: 2024/11/28 19:12:35 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sh_run(char *cmmnd, t_prompt *lst_node, char **envp)
{
	char	**cmmnds_args[3];
	int		exit_code;

	cmmnds_args[0] = sh_split_q (cmmnd, ';');
	cmmnds_args[1] = cmmnds_args[0];
	exit_code = EXIT_SUCCESS;
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
		{
			sh_ppfree(cmmnds_args[0]);
			free(cmmnd);
			run_builtins (cmmnds_args[2], envp, lst_node);
		}
		else
			exit_code = sh_execve (cmmnds_args[2], envp, cmmnds_args[0], cmmnd);
		sh_ppfree (cmmnds_args[2]);
		cmmnds_args[1]++;
	}
	return (sh_ppfree (cmmnds_args[0]), exit_code);
}

void	sp_print_cnf(char *cmmnd)
{
	write (1, cmmnd, ft_strlen (cmmnd));
	write (1, ": command not found\n", 20);
}

int	sh_execve(char **argv, char **envp, char **f_cmmnds, char *f_cmmnd)
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
			sh_err (ft_strjoin (argv[0], ": command not found"));
		sh_ppfree (argv);
		exit (rp);
	}
	waitpid (pid, &rp, 0);
	return (WEXITSTATUS(rp));
}
