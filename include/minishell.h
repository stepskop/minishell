/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:27:51 by ksorokol          #+#    #+#             */
/*   Updated: 2024/11/20 16:57:24 by ksorokol         ###   ########.fr       */
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
# include <signal.h>
# include <sys/types.h>

# define PPS "sksh: "

typedef struct s_counters_quotes
{
	unsigned int	single_quote;
	unsigned int	double_quote;
}	t_counters_quotes;

// utils001.c
size_t	sh_strlen(const char *s);
int		sh_check_eol(char *cmmnd);
int		sh_backslash(char **line);
char	*sh_strjoin(char *s1, char *s2);

// execve.c
int		sh_execve(char *cmmnd);
char	**sh_semicolon(char *cmmnd);
char	**sh_app_args(char *cmmnd);

// signal.c
void	sigact(int sig, siginfo_t *info, void *context);
void	sig_init(void);
#endif
