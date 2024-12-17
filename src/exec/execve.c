/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:34:17 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/16 15:45:01 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_builtins(char *cmmnd);

int	sh_run(char *cmmnd, t_ctx ctx)
{
	char	**cmmnds_args[3];
	int		exit_code;

	cmmnds_args[0] = sh_split_q (cmmnd, ';');
	free(cmmnd);
	cmmnds_args[1] = cmmnds_args[0];
	exit_code = EXIT_SUCCESS;
	while (*cmmnds_args[1])
	{
		cmmnds_args[2] = sh_ud_rmbs (sh_split_q (*cmmnds_args[1], ' '));
		if (check_builtins (cmmnds_args[2][0]) == 1)
			run_builtins_01 (cmmnds_args[2], ctx);
		else if (check_builtins (cmmnds_args[2][0]) == 2)
		{
			if (!ft_strncmp (cmmnds_args[2][0], "exit", 4))
			{
				close(ctx.stdin_fd);
				sh_ppfree(cmmnds_args[0]);
			}
			run_builtins_02 (cmmnds_args[2], ctx);
		}
		else
			exit_code = sh_execve (cmmnds_args[2], ctx.envp, ctx.pipefd);
		sh_ppfree (cmmnds_args[2]);
		cmmnds_args[1]++;
	}
	return (sh_ppfree (cmmnds_args[0]), exit_code);
}

static int	check_builtins(char *cmmnd)
{
	if (!ft_strncmp (cmmnd, "echo", ft_strlen (cmmnd))
		|| !ft_strncmp (cmmnd, "cd", ft_strlen (cmmnd))
		|| !ft_strncmp (cmmnd, "pwd", ft_strlen (cmmnd)))
		return (1);
	else if (!ft_strncmp (cmmnd, "export", ft_strlen (cmmnd))
		|| !ft_strncmp (cmmnd, "unset", ft_strlen (cmmnd))
		|| !ft_strncmp (cmmnd, "env", ft_strlen (cmmnd))
		|| !ft_strncmp (cmmnd, "exit", ft_strlen (cmmnd)))
		return (2);
	else
		return (0);
}

void	sp_print_cnf(char *cmmnd)
{
	write (2, cmmnd, ft_strlen (cmmnd));
	write (2, ": command not found\n", 20);
}

int	sh_execve(char **argv, char **envp, int pipefd[2])
{
	char	*cmmnd;
	int		rp;

	rp = 0;
	if (fork() == 0)
	{
		rl_clear_history ();
		rp = EXIT_SUCCESS;
		cmmnd = get_cmd (argv[0]);
		if (pipefd[1] > 1)
			dup2(pipefd[1], STDOUT_FILENO);
		if (pipefd[1] > 1)
			close(pipefd[1]);
		if (pipefd[0] > 0)
			close(pipefd[0]);
		if (cmmnd)
			rp = execve (cmmnd, argv, envp);
		else
			sp_print_cnf(argv[0]);
		sh_ppfree (argv);
		exit (EXIT_FAILURE);
	}
	else
	{
		if (pipefd[0] > 0)
			dup2(pipefd[0], STDIN_FILENO);
	}
	return (WEXITSTATUS(rp));
}
