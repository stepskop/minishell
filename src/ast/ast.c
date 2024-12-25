/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 00:06:52 by username          #+#    #+#             */
/*   Updated: 2024/12/25 03:56:07 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int	ast_eval(t_ast *ast, char ***penvp)
{
	if (ast->type == AST_VAL && (!ast->parent || \
		(ast->parent->res == 0 && ast->parent->type == AST_AND) || \
		(ast->parent->res == 1 && ast->parent->type == AST_OR) || \
		ast->parent->res == -1))
	{
		ast->res = ast_execute(ast, penvp);
		if (ast->parent)
			ast->parent->res = ast->res;
		return (ast->res);
	}
	if (ast->left)
	{
		ast->res = ast_eval(ast->left, penvp);
		if (ast->right && ((ast->res == 0 && ast->type == AST_AND) || \
			(ast->res == 1 && ast->type == AST_OR)))
			ast->res = ast_eval(ast->right, penvp);
		return (ast->res);
	}
	return (ast->parent->res);
}

int	ast_setop(t_ast **curr, t_ast_token op, char *str, char ***penvp)
{
	int	i;

	i = 2;
	(*curr) = (*curr)->parent;
	if ((*curr)->type != AST_EMPTY)
	{
		(*curr)->res = ast_eval((*curr)->left, penvp);
		if ((*curr)->left)
			free_ast((*curr)->left);
		(*curr)->left = (*curr)->right;
		(*curr)->right = NULL;
	}
	(*curr)->type = op;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	return (i);
}

int	ast_parse(char *pos, t_ast **curr, char ***penvp)
{
	int	i;

	if (pos[0] == '(')
		return (ast_initchild(curr));
	else if (pos[0] == '&' && (pos[1] == '&'))
		return (ast_setop(curr, AST_AND, &pos[0], penvp));
	else if (pos[0] == '|' && (pos[1] == '|'))
		return (ast_setop(curr, AST_OR, &pos[0], penvp));
	else if (pos[0] == ')')
	{
		i = 1;
		while ((pos[i] >= 9 && pos[i] <= 13) || pos[i] == 32)
			i++;
		return ((*curr) = (*curr)->parent, i);
	}
	else
	{
		if (!ast_initchild(curr))
			return (-1);
		return (ast_fill(*curr, pos));
	}
}

t_ast	*ast(char *str, char ***penvp)
{
	int		prompt_len;
	int		i;
	int		curr_len;
	t_ast	*curr;
	t_ast	*ast;

	i = 0;
	ast = ast_init();
	if (!ast)
		return (NULL);
	curr = ast;
	prompt_len = ft_strlen(str);
	while (prompt_len > i)
	{
		curr_len = ast_parse(&str[i], &curr, penvp);
		if (curr_len == -1)
			return (free_ast(ast), NULL);
		i += curr_len;
	}
	free(str);
	ast_eval(ast, penvp);
	free_ast(ast);
	return (NULL);
}
