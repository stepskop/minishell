/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 21:10:05 by username          #+#    #+#             */
/*   Updated: 2024/12/21 15:33:51 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "utils.h"

// run_builtins.c
int			is_builtin(char *cmmnd);
int			run_builtins(char **argv, t_ctx ctx);
int			run_exit(char **argv, t_ctx ctx, char *str, int exit_code);
// echo.c
void		echo(char **argv);

// pwd.c
void		pwd(void);

// cd.c
void		cd(char **argv);
char		*cd_home(char **argv);

// env.c
char		*sh_getenv(char *name, char **envp);
void		env(char **argv, char **envp);

// env01.c
void		env_print(char **envp);
int			env_prsng(char **argv, char ***penvp);
int			env_check_var(char *var);

// env02.c
char		**envp_copy(char **envp1, char **envp2);
int			envp_set_var(char ***envp, char *sv);

// export.c
void		export(char **argv, char ***envp);

// unset.c
void		unset(char **argv, char ***envp);

#endif
