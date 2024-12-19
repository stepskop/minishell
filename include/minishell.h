/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:27:51 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/19 18:20:54 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE

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
# include <linux/limits.h>
# include <fcntl.h>

# define PPS "sksh:"
# define SET 0
# define GET 1

typedef enum e_token
{
	CMD,
	WORD,
	PIPE,
	GREAT,
	GREATGREAT,
	LESS,
	LESSLESS,
	AND,
	OR,
}	t_token;

typedef struct s_ctx
{
	int				*pipefd;
	struct s_prompt	*node;
	char			**to_free;
	char			***penvp;
}	t_ctx;

typedef struct s_args
{
	char			*data;
	struct s_args	*next;
}	t_args;

typedef struct s_prompt
{
	int				in_fd;
	int				out_fd;
	char			*str_val;
	t_token			token;
	t_ctx			*cmd;
	t_args			*args;
	struct s_prompt	*next_cmd;
	struct s_prompt	*next;
	struct s_prompt	*prev;
}	t_prompt;

void		_loop_(char **envp);

// Lexer
t_prompt	*lexer(char **cmd_line);
void		print_lex_dbg(t_prompt *lst);

// Lexer - utils
int			lx_argcheck(t_prompt node);
void		lx_free_tokens(t_prompt *lst);
t_prompt	*lx_parent(t_prompt *curr, t_prompt *parent);
int			lx_cmdend(t_prompt curr);
t_prompt	*lx_setnext(t_prompt *old, t_prompt *new);
int			lx_parse(char *str, t_prompt **curr,
				t_prompt **last_par, t_prompt **last_cmd);

// Lexer - list_utils
t_prompt	*lx_add(t_token token, t_prompt *prev, char *val);
t_token		lx_get_token(char *str);

// Executor
int			executor(t_prompt *lst, char ***penvp);

// utils001.c
size_t		sh_strlen(const char *s);
int			sh_check_eol(char *cmmnd);
int			sh_backslash(char **line);
// char	*sh_strjoin(char *s1, char *s2);
void		sh_ppfree(char	**pp);
char		*sh_strdup(char *str);

// quotation.c
int			check_quot(char *str);
char		*del_quot(char *str);

// utils002.c
char		*sh_strjoin(char *s1, char *s2);
char		*put_env(char *str, char **envp);
char		*str_join_env(char *str, char *part1, size_t idx[], char **envp);
char		*get_env_name(char *dollar);
char		*strs_cat(char *str_a, char *str_b, char *str_c, size_t idx_b[]);

// utils003.c
char		*sh_strjoin_free(char *s1, char *s2, int opt);
void		sh_del_arr(void *arr[], int arr_size);
char		*sh_lst2str(t_list *lst, char c);
char		*sh_pstr2str(char **pstr, char c);
char		**sh_pstrdup(char **pstr);

// utils004.c
int			sh_pstr_size(char **pstr);
char		*sh_unquotes(char *arg);
char		sh_bsq(char *arg, size_t idx);
char		**sh_uq_args(char **args);

// utils005.c
char		*sh_rmbs(char *arg);
char		**sh_rmbs_args(char **args);
char		**sh_ud_rmbs(char **args);
int			sh_insq(char *arg, size_t pos);
size_t		sh_setchstr(char *str_d, size_t idx_d, char *str_s, size_t idx_s);

// sh_split_q.c
char		**sh_split_q(char *str, char c);

// asterisk01.c
char		*sh_asterisk(char *astr);

// a_split.c
t_list		*a_split(char *str, char c);
t_list		*a_split_elem(char *str, size_t idx[]);
void		a_split_clear(void *elem);

// execve.c
int			sh_run(char *cmmnd, t_ctx ctx);
int			sh_execve(char **argv, t_ctx ctx);
void		sh_subprocess_pipes(int pipefd[2]);
void		sp_print_cnf(char *cmmnd);

// signal.c
void		sig_init(void);

// path.c
char		*get_sh_path(int absolute_path);
char		*get_sh_pps(void);
char		*get_cmd(char *cmd);
char		*sh_replace_tilde(char *path);
char		*sh_replace_dot(char *path);

// run_builtins.c
// int			run_builtins(char **argv, char **envp, t_prompt *lst_node);
int			run_builtins_01(char **argv, t_ctx ctx);
int			run_builtins_02(char **argv, t_ctx ctx);
int			run_exit(char **argv, t_ctx ctx);

// echo.c
void		echo(char **argv);

// pwd.c
void		pwd(void);

// cd.c
void		cd(char **argv);
char		*cd_home(char **argv);

// env01.c
char		*sh_getenv(char *name, char **envp);
void		env(char **argv, char **envp);

// Err
void		sh_err(char *str);

// Memory
void		free_args(t_args *args);

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
// valgrind --trace-children=yes --suppressions=rl.supp ./minishell
