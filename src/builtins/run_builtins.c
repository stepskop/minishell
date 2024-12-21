/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 23:53:25 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/19 23:05:23 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"

static int	exec_builtin(char **argv, t_ctx ctx, int std_backup[2])
{
	int	result;

	result = 0;
	if (!ft_strcmp (argv[0], "echo"))
		result = echo (argv);
	else if (!ft_strcmp (argv[0], "pwd"))
		result = pwd ();
	else if (!ft_strcmp (argv[0], "env"))
		result = env (argv, sh_pstrdup (*ctx.penvp));
	else if (!ft_strcmp (argv[0], "cd"))
		result = cd (argv);
	else if (!ft_strcmp (argv[0], "export"))
		result = export (argv, ctx.penvp);
	else if (!ft_strcmp (argv[0], "unset"))
		result = unset (argv, ctx.penvp);
	else if (!ft_strcmp (argv[0], "exit"))
	{
		if (std_backup)
			close_pipe(std_backup);
		result = run_exit (argv, ctx, "exit\n", EXIT_SUCCESS);
	}
	return (result);
}

static int	is_pipeline(t_prompt *node)
{
	t_prompt	*curr;

	curr = node;
	while (curr && curr->token != AND && curr->token != OR)
	{
		if (curr->token == PIPE)
			return (1);
		curr = curr->prev;
	}
	curr = node;
	while (curr && curr->token != AND && curr->token != OR)
	{
		if (curr->token == PIPE)
			return (1);
		curr = curr->next;
	}
	return (0);
}

int	is_builtin(char *cmmnd)
{
	if (!ft_strcmp (cmmnd, "echo")
		|| !ft_strcmp (cmmnd, "env")
		|| !ft_strcmp (cmmnd, "pwd")
		|| !ft_strcmp (cmmnd, "export")
		|| !ft_strcmp (cmmnd, "unset")
		|| !ft_strcmp (cmmnd, "cd")
		|| !ft_strcmp (cmmnd, "exit"))
		return (1);
	return (0);
}

int	run_builtins(char **argv, t_ctx ctx)
{
	int	pid;
	int	sub_proc;
	int	status;
	int	std_backup[2];

	pid = -1;
	sub_proc = is_pipeline(ctx.node);
	if (sub_proc)
		pid = fork();
	if (pid == 0)
	{
		ex_subprocess_pipes(ctx.pipefd);
		exit(exec_builtin(argv, ctx, NULL));
	}
	else if (!sub_proc)
	{
		ex_processless_pipes(ctx.pipefd, std_backup);
		status = exec_builtin(argv, ctx, std_backup);
		ctx.node->proc_less = 1;
		ctx.node->pid = status;
		restore_stdfd(std_backup);
		return (status);
	}
	ctx.node->pid = pid;
	return (pid);
}

int	run_exit(char **argv, t_ctx ctx, char *str, int exit_code)
{
	t_prompt	*curr;

	if (str)
		write (1, str, ft_strlen (str));
	curr = ctx.node;
	while (curr && curr->prev)
		curr = curr->prev;
	free_prompt(curr);
	sh_ppfree (argv);
	sh_ppfree (ctx.to_free);
	sh_ppfree (*ctx.penvp);
	rl_clear_history ();
	exit (exit_code);
}
