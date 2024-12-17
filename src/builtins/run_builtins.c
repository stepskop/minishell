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

// int	run_builtins(char **argv, char **envp, t_prompt *lst_node)
// {
// 	t_prompt	*curr;

// 	if (!ft_strcmp (argv[0], "exit"))
// 	{
// 		curr = lst_node;
// 		while (curr && curr->prev)
// 			curr = curr->prev;
// 		lx_free_tokens(curr);
// 		sh_ppfree (argv);
// 		exit (EXIT_SUCCESS);
// 	}
// 	else if (!ft_strcmp (argv[0], "echo")
// 		|| !ft_strncmp (argv[0], "echo ", 5))
// 		echo (argv);
// 	else if (!ft_strcmp (argv[0], "pwd")
// 		|| !ft_strncmp (argv[0], "pwd ", 4))
// 		pwd ();
// 	else if (!ft_strcmp (argv[0], "cd")
// 		|| !ft_strncmp (argv[0], "cd ", 3))
// 		cd (argv);
// 	else if (!ft_strcmp (argv[0], "env")
// 		|| !ft_strncmp (argv[0], "env ", 4))
// 		env (argv, envp);
// 	return (0);
// }

// echo, cd, pwd
int	run_builtins_01(char **argv, char **envp, t_prompt *lst_node, int pipefd[2], int stdin_fd)
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
			dup2(pipefd[1], STDOUT_FILENO);
		if (pipefd[1] > 1)
			close(pipefd[1]);
		if (pipefd[0] > 0)
			close(pipefd[0]);
		close(stdin_fd);
		if (!ft_strcmp (argv[0], "echo")
			|| !ft_strncmp (argv[0], "echo ", 5))
			echo (argv);
		else if (!ft_strcmp (argv[0], "pwd"))
			pwd ();
		else if (!ft_strcmp (argv[0], "cd"))
			cd (argv);
		run_exit (argv, envp, lst_node, pipefd, stdin_fd);
	}
	else
		if (pipefd[0] > 0)
			dup2(pipefd[0], STDIN_FILENO);
	return (0);
}

int	run_builtins_02(char **argv, char **envp, t_prompt *lst_node, int pipefd[2], int stdin_fd)
{
	int	pid;

	if (!ft_strcmp (argv[0], "exit"))
	{
		sh_ppfree (((t_pv *)sh_get_pv ())->envp);
		run_exit (argv, envp, lst_node, pipefd, stdin_fd);
	}
	pid = fork();
	if (pid == 0)
	{
		// sh_ppfree (((t_pv *)sh_get_pv ())->envp);	// env - Invalid free() / delete / delete[] / realloc() 
		sh_get_pv()->envp = envp;
		if (pipefd[1] > 1)
			dup2(pipefd[1], STDOUT_FILENO);
		close(stdin_fd);
		if (pipefd[1] > 1)
			close(pipefd[1]);
		if (pipefd[0] > 0)
			close(pipefd[0]);
		if (!ft_strcmp (argv[0], "env")
			|| !ft_strncmp (argv[0], "env ", 4))
			env (argv, envp, stdin_fd);
		run_exit (argv, envp, lst_node, pipefd, stdin_fd);
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
