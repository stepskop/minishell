/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 14:48:27 by username          #+#    #+#             */
/*   Updated: 2024/12/25 03:52:25 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "lexer.h"
#include "exec.h"

t_ast	*ast_new(char *value, t_ast_token token, t_ast *parent)
{
	t_ast	*new_node;

	new_node = malloc(sizeof(t_ast));
	if (!new_node)
		return (perror("malloc"), NULL);
	new_node->res = -1;
	new_node->type = token;
	new_node->value = value;
	new_node->parent = parent;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

int	ast_initchild(t_ast **curr)
{
	t_ast	*new_node;

	new_node = ast_new(NULL, AST_EMPTY, *curr);
	if (!new_node)
		return (-1);
	if (!(*curr)->left)
		(*curr)->left = new_node;
	else
		(*curr)->right = new_node;
	*curr = new_node;
	return (1);
}

void	ast_setchild(t_ast *node, t_ast *left, t_ast *right)
{
	if (!node)
		return ;
	if (left)
		node->left = left;
	if (right)
		node->right = right;
}

int	ast_execute(t_ast *node, char ***envp)
{
	char		*tmp;
	char		**splitted;
	t_prompt	*lst;

	tmp = put_env(node->value, *envp);
	splitted = sh_split_q(tmp, ' ');
	free(tmp);
	if (!splitted || !splitted[0])
		return (-1);
	lst = lexer(splitted);
	node->res = executor(lst, node, envp);
	free_prompt(lst);
	return (node->res);
}

t_ast	*ast_init(void)
{
	t_ast	*new_ast;

	new_ast = ast_new(NULL, AST_EMPTY, NULL);
	if (!new_ast)
		return (NULL);
	return (new_ast);
}
