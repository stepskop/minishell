/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 23:53:25 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/18 15:00:47 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// echo, cd, pwd
int	run_builtins_01(char **argv, t_ctx ctx)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (ctx.pipefd[1] > 1)
			dup2(ctx.pipefd[1], STDOUT_FILENO);
		if (ctx.pipefd[1] > 1)
			close(ctx.pipefd[1]);
		if (ctx.pipefd[0] > 0)
			close(ctx.pipefd[0]);
		close(ctx.stdin_fd);
		if (!ft_strcmp (argv[0], "echo")
			|| !ft_strncmp (argv[0], "echo ", 5))
			echo (argv);
		else if (!ft_strcmp (argv[0], "pwd"))
			pwd ();
		else if (!ft_strcmp (argv[0], "cd"))
			cd (argv);
		run_exit (argv, ctx);
	}
	else
		if (ctx.pipefd[0] > 0)
			dup2(ctx.pipefd[0], STDIN_FILENO);
	return (0);
}

int	run_builtins_02(char **argv, t_ctx ctx)
{
	int	pid;

	if (!ft_strcmp (argv[0], "exit"))
		run_exit (argv, ctx);
	pid = fork();
	if (pid == 0)
	{
		if (ctx.pipefd[1] > 1)
			dup2(ctx.pipefd[1], STDOUT_FILENO);
		close(ctx.stdin_fd);
		if (ctx.pipefd[1] > 1)
			close(ctx.pipefd[1]);
		if (ctx.pipefd[0] > 0)
			close(ctx.pipefd[0]);
		if (!ft_strcmp (argv[0], "env")
			|| !ft_strncmp (argv[0], "env ", 4))
			env (argv, NULL, ctx.stdin_fd);
		run_exit (argv, ctx);
	}
	else
	{
		if (ctx.pipefd[0] > 0)
			dup2(ctx.pipefd[0], STDIN_FILENO);
	}
	return (0);
}

int	run_exit(char **argv, t_ctx ctx)
{
	t_prompt	*curr;

	curr = ctx.node;
	close(ctx.stdin_fd);
	while (curr && curr->prev)
		curr = curr->prev;
	lx_free_tokens(curr);
	sh_ppfree (argv);
	sh_ppfree (ctx.to_free);
	sh_ppfree (sh_get_pv()->envp);
	rl_clear_history ();
	exit (EXIT_SUCCESS);
}
