/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:58:14 by username          #+#    #+#             */
/*   Updated: 2024/12/27 04:02:43 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "utils.h"

// Executor
int			executor(t_prompt *lst, t_ast *ast, char ***penvp);
int			ex_get_heredoc(t_args *args);
int			ex_open_file(t_args *args, int oflag, char **envp);
size_t		ex_cmdlen(t_args *args);
int			ex_expand(t_args *args, char **envp);
void		clean_pipes(t_prompt *node, int pipefd[2]);

// Exec
int			sh_run(char *cmmnd, t_ctx ctx);
int			sh_execve(char **argv, t_ctx ctx);
void		ex_subprocess_pipes(int pipefd[2]);
void		close_pipe(int pipefd[2]);
void		sp_print_cnf(char *cmmnd);
int			ex_get_exitcode(t_prompt *node);
void		std_pipe(int pipefd[2]);
void		close_unused_fd(t_ctx ctx);

#endif
