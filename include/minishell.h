/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:27:51 by ksorokol          #+#    #+#             */
/*   Updated: 2024/11/27 19:47:04 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <dirent.h>
# include <errno.h>

# define PPS "sksh:"

typedef struct s_counters_quotes
{
	unsigned int	single_quote;
	unsigned int	double_quote;
}	t_counters_quotes;

void	_loop_(char **envp);

// utils001.c
size_t	sh_strlen(const char *s);
int		sh_check_eol(char *cmmnd);
int		sh_backslash(char **line);
char	*sh_strjoin(char *s1, char *s2);
void	sh_ppfree(char	**pp);

// utils002.c
char	*sh_strcat(char *s1, char *s2);
char	*put_env(char *str);
char	*str_join_env(char *str, char *part1, size_t idx[]);
char	*get_env_name(char *dollar);
char	*strs_cat(char *str_a, char *str_b, char *str_c, size_t idx_b[]);

// sh_split_q.c
char	**sh_split_q(char *str, char c);
char	*sh_split_map(char *str, char c);
int		sh_split_couont(char *map, size_t len);
char	*sh_split_element(char *map, size_t len, int elem);

// execve.c
int		sh_run(char *cmmnd, char **envp);
void	sp_print_cnf(char *cmmnd);
void	sh_execve(char **argv, char **envp, char **f_cmmnds, char *f_cmmnd);

// signal.c
void	sig_init(void);
void	sigact(int sig, siginfo_t *info, void *context);

// path.c
char	*get_sh_path(int absolute_path);
char	*get_sh_pps(void);
char	*get_cmd(char *cmd);

// run_builtins.c
int		run_builtins(char **argv, char **envp);

// echo.c
void	echo(char **argv);
void	echo_write(char *arg);
size_t	echo_dollar(char *dollar);
size_t	echo_slash(char *slash);

// pwd.c
void	pwd(void);

// cd.c
void	cd(char **argv);
char	*cd_home(char **argv);

// env.c
void	env(char **envp);

#endif

// valgrind
// --fair-sched=yes
// --trace-children=yes
// --tool=memcheck
// --leak-check=full
// --show-leak-kinds=all
// --tool=helgrind
// --tool=drd
// --read-var-info=yes
// --show-reachable=yes
