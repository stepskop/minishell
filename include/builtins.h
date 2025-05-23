/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 21:10:05 by username          #+#    #+#             */
/*   Updated: 2024/12/27 11:32:33 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "utils.h"

// run_builtins.c
int			is_builtin(char *cmmnd);
int			run_builtins(char **argv, t_ctx ctx);
int			run_exit(char **argv, t_ctx ctx, int exit_code, char *str2free);

// builtin_utils.c
void		restore_stdfd(int pipefd[2]);
void		processless_pipes(int pipefd[2], int std_backup[2]);

// echo.c
int			echo(char **argv);

// pwd.c
int			pwd(char **envp);

// cd.c
int			cd(char **argv, char **envp);
char		*cd_home(char **argv, char **envp);

// env.c
char		*sh_getenv(char *name, char **envp);
int			env(char **argv, char **envp);

// env01.c
void		env_print(char **envp);
int			env_prsng(char **argv, char ***penvp);
int			env_check_var(char *var, int e_code);

// env02.c
char		**envp_copy(char **envp1, char **envp2);
int			envp_set_var(char ***envp, char *sv, int e_code);

// export.c
int			export(char **argv, char ***envp);

// unset.c
int			unset(char **argv, char ***envp);

// exit.c
int			_exit_(char **argv, t_ctx ctx, int std_backup[2]);

#endif
