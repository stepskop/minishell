/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 00:07:09 by username          #+#    #+#             */
/*   Updated: 2024/12/25 03:56:36 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "minishell.h"
# include "utils.h"

t_ast	*ast(char *str, char ***penvp);
t_ast	*ast_init(void);
int		ast_initchild(t_ast **curr);
int		ast_execute(t_ast *node, char ***envp);
void	ast_setchild(t_ast *node, t_ast *left, t_ast *right);
t_ast	*ast_new(char *value, t_ast_token token, t_ast *parent);
int		ast_fill(t_ast *node, char *str);

// DEBUG - will be deleted
void	draw_ast(t_ast *ast);

#endif
