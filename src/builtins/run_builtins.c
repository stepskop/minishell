/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 23:53:25 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/19 18:13:52 by ksorokol         ###   ########.fr       */
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
		if (!ft_strcmp (argv[0], "env"))
			env (argv, sh_pstrdup (*ctx.penvp));
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
	sh_ppfree (ctx.to_free);
	sh_ppfree (*ctx.penvp);
	rl_clear_history ();
	exit (EXIT_SUCCESS);
}
