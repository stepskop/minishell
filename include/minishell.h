/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:27:51 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/01 13:46:44 by ksorokol         ###   ########.fr       */
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

typedef struct s_args
{
	char			*data;
	struct s_args	*next;
}	t_args;

typedef struct s_input
{
	char			*str_val;
	t_token			token;
	t_args			*args;
	struct s_input	*next;
	struct s_input	*prev;
}	t_input;

typedef struct s_counters_quotes
{
	unsigned int	single_quote;
	unsigned int	double_quote;
}	t_counters_quotes;

typedef struct s_dir_element
{
	unsigned char	d_type;
	char			*d_name;
	char			*full_name;
	char			*rel_name;
}	t_de;

void	_loop_(char **envp);

// Lexer
t_input	*lexer(char **cmd_line);
void	print_lex_dbg(t_input *lst);

// Lexer utils
int		lx_add_arg(char *str, t_args **args);
t_token	lx_get_token(char *str);
void	lx_free_tokens(t_input *lst);
int		lx_accept_sub(t_input node);

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

// utils003.c
char	*sh_strcat_free(char *s1, char *s2, int opt);
void	sh_del_arr(void *arr[], int arr_size);

// sh_split_q.c
char	**sh_split_q(char *str, char c);
char	*sh_split_map(char *str, char c);
int		sh_split_couont(char *map, size_t len);
char	*sh_split_element(char *map, size_t len, int elem);

// asterisk.c
t_list	*sh_asterisk(char *astr);
t_list	*get_dirs(char *pattern);
int		get_lst_dirs(t_list **lst, char *pattern, char *path[]);
void	aster_recursion(t_list *dir, t_list *dirs, t_list **result);
int		wildcard_check(char *wildcard, char *str);

// asterisk02.c
char	*sh_remove_last_c(char *str, char c);
t_de	*sh_new_de(unsigned char d_type, char *d_name, char *path[]);
void	dirs_clean(void *content);
int		dirs_check(char *d_name, char *pttrn, unsigned char d_type);
void	dirs_init(t_list *dirs[], char *pathes[], t_list *dir);
void	dirs_print(void *content);
void	list_print(void *content);

// a_split.c
t_list	*a_split(char *str, char c);
t_list	*a_split_elem(char *str, size_t idx[]);
void	a_split_clear(void *elem);

// execve.c
int		sh_run(char *cmmnd, char **envp);
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
