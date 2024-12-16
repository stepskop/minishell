/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 23:53:25 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/16 16:04:59 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_builtins_01(char **argv, char **envp, t_prompt *lst_node, int pipefd[2])
{
	int	pid;

	(void)envp;
	(void)lst_node;
	(void)pipefd;
	pid = fork();
	if (pid == 0)
	{
		sh_ppfree (((t_pv *)sh_get_pv ())->envp);
		sh_get_pv()->envp = envp;
		if (pipefd[1] > 1)
			close(pipefd[0]);
		if (pipefd[1] > 1)
			dup2(pipefd[1], STDOUT_FILENO);
		if (!ft_strcmp (argv[0], "echo"))
			echo (argv);
		else if (!ft_strcmp (argv[0], "pwd"))
			pwd ();
		else if (!ft_strcmp (argv[0], "cd"))
			cd (argv);
		run_exit (argv, envp, lst_node, pipefd);
	}
	else
		if (pipefd[0] > 0)
			dup2(pipefd[0], STDIN_FILENO);
	return (0);
}

int	run_builtins_02(char **argv, char **envp, t_prompt *lst_node, int pipefd[2])
{
	int	pid;

	if (!ft_strcmp (argv[0], "exit"))
	{
		sh_ppfree (((t_pv *)sh_get_pv ())->envp);
		run_exit (argv, envp, lst_node, pipefd);
	}
	pid = fork();
	if (pid == 0)
	{
		// sh_ppfree (((t_pv *)sh_get_pv ())->envp);	// env - Invalid free() / delete / delete[] / realloc() 
		sh_get_pv()->envp = envp;
		if (pipefd[1] > 1)
			close(pipefd[0]);
		if (pipefd[1] > 1)
			dup2(pipefd[1], STDOUT_FILENO);
		if (!ft_strcmp (argv[0], "env"))
			env (argv, envp);
		run_exit (argv, envp, lst_node, pipefd);
	}
	else
	{
		if (pipefd[0] > 0)
			dup2(pipefd[0], STDIN_FILENO);
	}
	return (0);
}

int	run_exit(char **argv, char **envp, t_prompt *lst_node, int pipefd[2])
{
	t_prompt	*curr;

	(void) envp;
	(void) pipefd;
	curr = lst_node;
	while (curr && curr->prev)
		curr = curr->prev;
	lx_free_tokens(curr);
	sh_ppfree (argv);
	rl_clear_history ();
	exit (EXIT_SUCCESS);
}
