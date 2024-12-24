/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 00:06:52 by username          #+#    #+#             */
/*   Updated: 2024/12/24 02:40:57 by username         ###   ########.fr       */
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
	new_node->sibling = NULL;
	return (new_node);
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

int	ast_setop(t_ast **curr, t_ast_token op)
{
	(*curr)->parent->type = op;
	if (!ast_initchild(curr))
		return (-1);
	return (2);
}

int	ast_execute(t_ast *node, char ***envp)
{
	char		*tmp;
	char		**splitted;
	t_prompt	*lst;

	tmp = put_env(node->value, *envp);
	splitted = sh_split_q(tmp, ' ');
	free(tmp);
	if (splitted && splitted[0])
		return (-1);
	lst = lexer(splitted);
	node->res = executor(lst, envp);
	free_prompt(lst);
	return (node->res);
}

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

int	ast_fill(t_ast *node, char *str)
{
	int	i;
	int	start;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	start = i;
	while (str[i] && (str[i] != '&' && str[i] != '|' && \
		str[i] != '(' && str[i] != ')'))
	{
		if (str[i++] == '\'')
			while (str[i] && str[i] != '\'')
				;
		if (str[i++] == '\"')
			while (str[i] && str[i] != '\"')
				;
		if (str[i])
			i++;
	}
	node->type = AST_VAL;
	node->value = ft_substr(str, start, i - start);
	if (!node->value)
		return (-1);
	return (i);
}

int	ast_parse(char *pos, t_ast **curr, char ***penvp)
{
	if (pos[0] == '(')
		return (ast_initchild(curr));
	else if (pos[0] == '&' && (pos[1] == '&'))
		return (ast_setop(curr, AST_AND));
	else if (pos[0] == '|' && (pos[1] == '|'))
		return (ast_setop(curr, AST_OR));
	else if (pos[0] == ')')
		return (ast_eval(curr, penvp));
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

	ast = ast_new(NULL, AST_EMPTY, NULL);
	if (!ast)
		return (NULL);
	i = 0;
	prompt_len = ft_strlen(str);
	curr = ast;
	while (prompt_len > i)
	{
		curr_len = ast_parse(&str[i], &curr, penvp);
		if (curr_len == -1)
			return (free_ast(ast), NULL);
		i += curr_len;
	}
	if (curr->res == -1)
		ast_execute(curr, penvp);
	return (ast);
}
