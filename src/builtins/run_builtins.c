/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 23:53:25 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/18 17:30:28 by ksorokol         ###   ########.fr       */
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
		sh_subprocess_pipes(ctx.pipefd);
		if (!ft_strcmp (argv[0], "echo"))
			echo (argv);
		else if (!ft_strcmp (argv[0], "pwd"))
			pwd ();
		else if (!ft_strcmp (argv[0], "cd"))
			cd (argv);
		run_exit (argv, ctx);
	}
	return (pid);
}

int	run_builtins_02(char **argv, t_ctx ctx)
{
	int	pid;

	if (!ft_strcmp (argv[0], "exit"))
		run_exit (argv, ctx);
	pid = fork();
	if (pid == 0)
	{
		sh_subprocess_pipes(ctx.pipefd);
		if (!ft_strcmp (argv[0], "env")
			|| !ft_strncmp (argv[0], "env ", 4))
			env (argv, NULL);
		run_exit (argv, ctx);
	}
	return (pid);
}

int	run_exit(char **argv, t_ctx ctx)
{
	t_prompt	*curr;

	curr = ctx.node;
	while (curr && curr->prev)
		curr = curr->prev;
	lx_free_tokens(curr);
	sh_ppfree (argv);
	//TODO: Invalid free
	//sh_ppfree (ctx.to_free);
	sh_ppfree (sh_get_pv()->envp);
	rl_clear_history ();
	exit (EXIT_SUCCESS);
}
