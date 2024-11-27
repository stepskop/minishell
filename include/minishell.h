/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:27:51 by ksorokol          #+#    #+#             */
/*   Updated: 2024/11/27 19:26:59 by username         ###   ########.fr       */
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

typedef enum e_token
{
	CMD,
	WORD,
	PIPE,
	GREAT,
	GREATGREAT,
	LESS,
	LESSLESS,
	LAST_STATUS,
	AND,
	OR,
}	t_token;

typedef struct s_cmd
{
	int		in_fd;
	int		out_fd;
	char	*path;
	char	**cmd_line;
	int		pid;
	char	**envp;
}	t_cmd;

typedef	struct s_args
{
	char			*data;
	struct s_args 	*next;
}	t_args;

typedef struct s_prompt
{
	char			*str_val;
	t_token			token;
	t_cmd			*cmd;
	t_args			*args;
	struct s_prompt	*next;
	struct s_prompt *prev;
}	t_prompt;

typedef struct s_counters_quotes
{
	unsigned int	single_quote;
	unsigned int	double_quote;
}	t_counters_quotes;

void	_loop_(void);

// Lexer
t_prompt	*lexer(char **cmd_line, char **envp);
t_prompt 	*lex_add(t_token token, t_prompt *prev);

// Lexer utils
int			add_arg(char *str, t_args **args);

// utils001.c
size_t	sh_strlen(const char *s);
int		sh_check_eol(char *cmmnd);
int		sh_backslash(char **line);
char	*sh_strjoin(char *s1, char *s2);
void	sh_ppfree(char	**pp);

// utils002.c
char	*sh_strcat(char *s1, char *s2);

// sh_spit_q.c
char	**sh_spit_q(char *str, char c);
char	*sh_spit_map(char *str, char c);
int		sh_spit_couont(char *map, size_t len);
char	*sh_spit_element(char *map, size_t len, int elem);

// execve.c
int		sh_run(char *cmmnd);
void	sp_print_cnf(char *cmmnd);
void	sh_execve(char **argv, char **envp, char **f_cmmnds, char *f_cmmnd);
int		cmmdn_running(int f);

// signal.c
void	sig_init(void);
void	sigact(int sig, siginfo_t *info, void *context);

// path.c
char	*get_sh_path(int absolute_path);
char	*get_sh_pps(void);
char	*get_cmd(char *cmd);

// run_builtins.c
int		run_builtins(char **argv);

// echo.c
void	echo(char **argv);
void	echo_write(char *arg);
size_t	echo_dollar(char *dollar);

// pwd.c
void	pwd(void);

// cd.c
void	cd(char **argv);
char	*cd_home(char **argv);

// Err
void	sh_err(char *str);
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
