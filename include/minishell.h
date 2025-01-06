/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:27:51 by ksorokol          #+#    #+#             */
/*   Updated: 2025/01/06 21:26:17 by ksorokol         ###   ########.fr       */
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

// Colors & Styles
# define CWD_COLOR "\001\033[0m\033[34m\002"
# define RESET_COLOR "\001\033[0m\002 "
// # define CWD_COLOR ""
// # define RESET_COLOR ""
# define KSOROKOL "\001\033[35m\033[1m\033[4m\002ksorokol"
# define SSKOPEK "\001\033[35m\033[1m\033[4m\002sskopek"

# define PPS "\001\033[1m\033[44m\033[97m\002 SKSH \001\033[0m\002 "
// # define PPS "SKSH "
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
	int				next_readpipe;
	struct s_prompt	*node;
	struct s_ast	*ast;
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
	int				io_err;
	char			*str_val;
	t_token			token;
	t_ctx			*cmd;
	int				proc_less;
	int				pid;
	t_args			*args;
	struct s_prompt	*next_cmd;
	struct s_prompt	*next;
	struct s_prompt	*prev;
}	t_prompt;

typedef enum e_ast_token
{
	AST_AND,
	AST_OR,
	AST_VAL,
	AST_EMPTY,
}	t_ast_token;

typedef struct s_ast
{
	int				res;
	char			*value;
	t_ast_token		type;
	struct s_ast	*left;
	struct s_ast	*right;
	struct s_ast	*parent;
}	t_ast;

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
/*
valgrind --trace-children=yes \
--leak-check=full \
--show-leak-kinds=all \
--suppressions=rl.supp ./minishell

valgrind --trace-children=yes \
--log-fd=9 9>>/home/ksorokol/GitHub/minishell/vg.log \
--leak-check=full \
--show-leak-kinds=all \
--suppressions=/home/ksorokol/GitHub/minishell/rl.supp \
./minishell
*/
