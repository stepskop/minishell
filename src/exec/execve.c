/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:34:17 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/30 01:47:06 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtins.h"
#include "path.h"
#include "signals.h"

int	sh_run(char *cmmnd, t_ctx ctx)
{
	char	**cmmnds_args[3];
	int		pid;

	cmmnds_args[0] = sh_split_q (cmmnd, ';');
	ctx.to_free = cmmnds_args[0];
	free(cmmnd);
	cmmnds_args[1] = cmmnds_args[0];
	pid = 0;
	if (!cmmnds_args[1])
		return (ctx.node->proc_less = 1, ctx.node->pid = 1, 1);
	while (*cmmnds_args[1])
	{
		cmmnds_args[2] = sh_ud_rmbs (sh_split_q (*cmmnds_args[1], ' '));
		if (!cmmnds_args[2])
			return (ctx.node->proc_less = 1,
				ctx.node->pid = 1, sh_ppfree(cmmnds_args[0]), 1);
		if (is_builtin(cmmnds_args[2][0]))
			pid = run_builtins(cmmnds_args[2], ctx);
		else
			pid = sh_execve (cmmnds_args[2], ctx);
		sh_ppfree (cmmnds_args[2]);
		cmmnds_args[1]++;
	}
	return (sh_ppfree (cmmnds_args[0]), pid);
}

void	sp_print_cnf(char *cmmnd)
{
	char	*str;

	if (ft_strchr (cmmnd, '/'))
		str = sh_strjoin (cmmnd, ": No such file or directory\n");
	else
		str = sh_strjoin (cmmnd, ": command not found\n");
	sh_err (str);
	free (str);
}

int	ex_get_exitcode(t_prompt *lst)
{
	int			status;
	int			curr_status;
	int			waited_pid;
	t_prompt	*curr;

	curr = lst;
	status = 0;
	waited_pid = 0;
	while (curr && curr->next_cmd)
		curr = curr->next_cmd;
	while (waited_pid != -1 || errno != ECHILD)
	{
		waited_pid = waitpid(-1, &curr_status, 0);
		if (waited_pid == curr->pid)
			status = curr_status;
	}
	if (lst && curr->proc_less)
		return (curr->pid);
	if (WIFSIGNALED(status))
		status = 128 + WTERMSIG(status);
	else if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}

int	sh_execve(char **argv, t_ctx ctx)
{
	char	*cmmnd;
	int		pid;
	int		exit_code;

	pid = fork();
	if (pid == 0)
	{
		sig_reset ();
		rl_clear_history ();
		cmmnd = path_resolve(argv[0], *(ctx.penvp));
		ex_subprocess_pipes(ctx.pipefd);
		close_unused_fd(ctx);
		if (cmmnd)
		{
			exit_code = sh_checkcmd (cmmnd);
			if (exit_code)
				run_exit (argv, ctx, exit_code, cmmnd);
			execve (cmmnd, argv, *(ctx.penvp));
		}
		else
			sp_print_cnf(argv[0]);
		run_exit (argv, ctx, 127, NULL);
	}
	ctx.node->pid = pid;
	return (pid);
}
