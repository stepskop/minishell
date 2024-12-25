/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:34:46 by username          #+#    #+#             */
/*   Updated: 2024/12/24 02:31:03 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_args(t_args *args)
{
	t_args	*tmp;

	while (args)
	{
		tmp = args->next;
		free(args->data);
		free(args);
		args = tmp;
	}
}

void	free_prompt(t_prompt *lst)
{
	t_prompt	*curr;
	t_prompt	*tmp;

	curr = lst;
	while (curr)
	{
		tmp = curr->next;
		free_args(curr->args);
		free(curr->str_val);
		free(curr);
		curr = tmp;
	}
}

void	free_ast(t_ast *ast)
{
	if (!ast)
		return ;
	free(ast->value);
	if (ast->left)
		free_ast(ast->left);
	if (ast->right)
		free_ast(ast->right);
	free(ast);
}

void	free_ast_node(t_ast *node)
{
	free(node->value);
	free(node);
}
