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

int	sh_run(char *cmmnd, t_prompt *lst_node, char **envp, int pipefd[2])
{
	//TODO: dont leak fd's
	char	**cmmnds_args[3];
	int		exit_code;

	cmmnds_args[0] = sh_split_q (cmmnd, ';');
	free(cmmnd);
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
			if (!ft_strncmp (cmmnds_args[2][0], "exit", 4))
				sh_ppfree(cmmnds_args[0]);
			run_builtins (cmmnds_args[2], envp, lst_node, pipefd);
		}
		else
			exit_code = sh_execve (cmmnds_args[2], envp, pipefd);
		sh_ppfree (cmmnds_args[2]);
		cmmnds_args[1]++;
	}
	return (sh_ppfree (cmmnds_args[0]), exit_code);
}

void	sp_print_cnf(char *cmmnd)
{
	write (2, cmmnd, ft_strlen (cmmnd));
	write (2, ": command not found\n", 20);
}

int	sh_execve(char **argv, char **envp, int pipefd[2])
{
	char	*cmmnd;
	pid_t	pid;
	int		rp;

	pid = fork ();
	rp = 0;
	if (pid == 0)
	{
		if (pipefd[1] > 1)
			close(pipefd[0]);
		rl_clear_history ();
		rp = EXIT_SUCCESS;
		cmmnd = get_cmd (argv[0]);
		if (pipefd[1] > 1)
			dup2(pipefd[1], STDOUT_FILENO);
		if (cmmnd)
			rp = execve (cmmnd, argv, envp);
		else
			sp_print_cnf(argv[0]);
		sh_ppfree (argv);
		exit (rp);
	}
	else
	{
		if (pipefd[0] > 0)
			dup2(pipefd[0], STDIN_FILENO);
	}
	return (WEXITSTATUS(rp));
}
