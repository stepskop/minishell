/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 00:06:52 by username          #+#    #+#             */
/*   Updated: 2024/12/24 15:03:26 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int	ast_eval(t_ast **curr, char ***penvp)
{
	*curr = (*curr)->parent;
	if ((*curr)->left && (*curr)->left->res == -1)
	{
		(*curr)->res = ast_execute((*curr)->left, penvp);
		if ((*curr)->res == -1)
			return (-1);
	}
	if (((*curr)->right && (*curr)->right->res == -1) && \
		(((*curr)->type == AST_AND && (*curr)->left->res == 0) || \
		((*curr)->type == AST_OR && (*curr)->left->res == 1)))
	{
		(*curr)->res = ast_execute((*curr)->right, penvp);
		if ((*curr)->res == -1)
			return (-1);
	}
	return (1);
}

int	ast_setop(t_ast **curr, t_ast_token op, char ***penvp)
{
	(*curr) = (*curr)->parent;
	if ((*curr)->right)
	{
		if ((*curr)->left->res == -1)
		{
			(*curr)->left->res = ast_execute((*curr)->left, penvp);
			if ((*curr)->left->res)
				return (-1);
			(*curr)->res = (*curr)->left->res;
		}
		if (((*curr)->left->res == 0 && (*curr)->type == AST_AND) || \
			((*curr)->left->res == 1 && (*curr)->type == AST_OR))
		{
			(*curr)->right->res = ast_execute((*curr)->right, penvp);
			(*curr)->res = (*curr)->right->res;
		}
		free_ast_node((*curr)->left);
		(*curr)->left = (*curr)->right;
		(*curr)->right = NULL;
	}
	(*curr)->type = op;
	if (!ast_initchild(curr) || (*curr)->left->res == -1)
		return (-1);
	return (2);
}

int	ast_fill(t_ast *node, char *str)
{
	int	i;
	int	start;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	start = i;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
		}
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
		}
		if (!str[i] || str[i] == '&' || (str[i] == '|' && str[i + 1] == '|') || \
			str[i] == '(' || str[i] == ')')
			break ;
		else
			i++;
	}
	node->type = AST_VAL;
	node->value = ft_substr(str, start, i - start);
	if (!node->value)
		return (-1);
	return (i);
}

int	ast_errproof_setop(char *str, int i, t_ast **node, char ***penvp)
{
	if (str[i] == '|')
	{
		if (ast_setop(node, AST_OR, penvp) == -1)
			return (-1);
	}
	else if (str[i] == '&')
		if (ast_setop(node, AST_AND, penvp) == -1)
			return (-1);
	return (i + 2);
}

int	ast_parse(char *pos, t_ast **curr, char ***penvp)
{
	int	i;

	if (pos[0] == '(')
		return (ast_initchild(curr));
	else if (pos[0] == '&' && (pos[1] == '&'))
		return (ast_setop(curr, AST_AND, penvp));
	else if (pos[0] == '|' && (pos[1] == '|'))
		return (ast_setop(curr, AST_OR, penvp));
	else if (pos[0] == ')')
	{
		i = ast_eval(curr, penvp);
		if (i == -1)
			return (-1);
		while ((pos[i] >= 9 && pos[i] <= 13) || pos[i] == 32)
			i++;
		if ((pos[i] == '&' && pos[i + 1] == '&') || \
			(pos[i] == '|' && pos[i + 1] == '|'))
			return (ast_errproof_setop(pos, i, curr, penvp));
		else
			return (-1);
	}
	else
		return (ast_fill(*curr, pos));
}

t_ast	*ast(char *str, char ***penvp)
{
	int		prompt_len;
	int		i;
	int		curr_len;
	t_ast	*curr;
	t_ast	*ast;

	i = 0;
	ast = ast_init(&curr);
	if (!ast)
		return (NULL);
	prompt_len = ft_strlen(str);
	while (prompt_len > i)
	{
		curr_len = ast_parse(&str[i], &curr, penvp);
		if (curr_len == -1)
			return (free_ast(ast), NULL);
		i += curr_len;
	}
	if (curr->res == -1 && (!curr->parent || curr->parent->res == -1 || \
		(curr->parent->res == 1 && curr->parent->type == AST_OR) || \
		(curr->parent->res == 0 && curr->parent->type == AST_AND)))
		ast_eval(&curr, penvp);
	free_ast_node(ast);
	return (NULL);
}
