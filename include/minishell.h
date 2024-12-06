/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:27:51 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/05 11:50:52 by ksorokol         ###   ########.fr       */
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

typedef struct s_prompt
{
	int				in_fd;
	int				out_fd;
	char			*str_val;
	t_token			token;
	t_cmd			*cmd;
	t_args			*args;
	struct s_prompt	*next_cmd;
	struct s_prompt	*next;
	struct s_prompt	*prev;
}	t_prompt;

typedef struct s_pipeline
{
	int		in_file;
}	t_pipeline;

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

void		_loop_(char **envp);

// Lexer
t_prompt	*lexer(char **cmd_line);
void		print_lex_dbg(t_prompt *lst);

// lexer_utils001
void		lx_free_tokens(t_prompt *lst);
t_prompt	*lx_parent(t_prompt *curr, t_prompt *parent);
int			lx_accept_sub(t_prompt node);
int			lx_cmdend(t_prompt curr);
t_prompt	*lx_lastcmd(t_prompt *old, t_prompt *new);

// lexer_utils002
int			lx_add_arg(char *str, t_args **args);
t_prompt	*lx_add(t_token token, t_prompt *prev, char *val);
t_token		lx_get_token(char *str);

// Executor
void		executor(t_prompt *lst, char **envp);
int			ex_get_heredoc(t_args *args);
int			ex_open_file(t_args *args, int oflag);

// utils001.c
size_t		sh_strlen(const char *s);
int			sh_check_eol(char *cmmnd);
int			sh_backslash(char **line);
// char	*sh_strjoin(char *s1, char *s2);
void		sh_ppfree(char	**pp);

// utils002.c
char		*sh_strjoin(char *s1, char *s2);
char		*put_env(char *str);
char		*str_join_env(char *str, char *part1, size_t idx[]);
char		*get_env_name(char *dollar);
char		*strs_cat(char *str_a, char *str_b, char *str_c, size_t idx_b[]);

// utils003.c
char	*sh_strjoin_free(char *s1, char *s2, int opt);
void	sh_del_arr(void *arr[], int arr_size);
char	*sh_lst2str(t_list *lst, char c);

// sh_split_q.c
char		**sh_split_q(char *str, char c);
char		*sh_split_map(char *str, char c);
int			sh_split_couont(char *map, size_t len);
char		*sh_split_element(char *map, size_t len, int elem);

// asterisk.c
char	*sh_asterisk(char *astr);
t_list	*get_dirs(char *pattern);
int		get_lst_dirs(t_list **lst, char *pattern, char *path[]);
void	aster_recursion(t_list *dir, t_list *dirs, t_list **result);
int		wildcard_check(char *wildcard, char *str);

// asterisk02.c
char	*sh_remove_last_c(char *str, char c);
t_de	*sh_new_de(unsigned char d_type, char *d_name, char *path[]);
void	dirs_clean(void *content);
int		dirs_check(char *d_name, char *pttrn);
void	dirs_init(t_list *dirs[], char *pathes[], t_list *dir);

// void	dirs_print(void *content);	//
// void	list_print(void *content);	//

// asterisk03.c
t_list	*aster_slash(char *pattern);
t_list	*aster_tilde(char *pattern);
t_list	*aster_dot(char *pattern);
t_list	*aster_start(t_list *dirs);
//int		check_d_type(t_list *dir);

// asterisk04.c
void	aster_order(t_list *result);
int		aster_pathcmp(char *path1, char *path2);
int		aster_strcmp(char *s1, char *s2);

// a_split.c
t_list	*a_split(char *str, char c);
t_list	*a_split_elem(char *str, size_t idx[]);
void	a_split_clear(void *elem);

// execve.c
int			sh_run(char *cmmnd, char **envp);
void		sh_execve(char **argv, char **envp, char **f_cmmnds, char *f_cmmnd);

// signal.c
void		sig_init(void);
void		sigact(int sig, siginfo_t *info, void *context);

// path.c
char		*get_sh_path(int absolute_path);
char		*get_sh_pps(void);
char		*get_cmd(char *cmd);
char		*sh_replace_tilde(char *path);
char		*sh_replace_dot(char *path);

// run_builtins.c
int			run_builtins(char **argv, char **envp);

// echo.c
void		echo(char **argv);
void		echo_write(char *arg);
size_t		echo_dollar(char *dollar);
size_t		echo_slash(char *slash);

// pwd.c
void		pwd(void);

// cd.c
void		cd(char **argv);
char		*cd_home(char **argv);

// env.c
void		env(char **envp);

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
