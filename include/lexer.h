/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 20:49:59 by username          #+#    #+#             */
/*   Updated: 2024/12/27 04:47:47 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"
# include "utils.h"

// Lexer
t_prompt	*lexer(char **cmd_line);
void		print_lex_dbg(t_prompt *lst);

// Lexer - utils
int			lx_argcheck(t_prompt node);
t_prompt	*lx_parent(t_prompt *curr, t_prompt *parent);
int			lx_cmdend(t_prompt curr);
t_prompt	*lx_setnext(t_prompt *old, t_prompt *new);
int			lx_parse(char *str, t_prompt **curr,
				t_prompt **last_par, t_prompt **last_cmd);
t_prompt	*lx_add(t_token token, t_prompt *prev, char *val);
t_token		lx_get_token(char *str);
int			lx_setlastcmd(t_prompt **last_par, t_prompt **last_cmd,
				t_prompt **curr, char *str);

#endif
