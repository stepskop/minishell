/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_fill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 03:55:48 by username          #+#    #+#             */
/*   Updated: 2024/12/25 03:58:32 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static int	ast_cmdlen(char *str, int i)
{
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
	return (i);
}

int	ast_fill(t_ast *node, char *str)
{
	int	i;
	int	start;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	start = i;
	i = ast_cmdlen(str, i);
	node->type = AST_VAL;
	node->value = ft_substr(str, start, i - start);
	if (!node->value)
		return (-1);
	return (i);
}
