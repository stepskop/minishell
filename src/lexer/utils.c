/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils001.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:15:35 by username          #+#    #+#             */
/*   Updated: 2024/12/06 00:29:56 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lx_argcheck(t_prompt node)
{
	if (node.token == CMD)
		return (1);
	else if ((node.token == GREAT || node.token == GREATGREAT || \
		node.token == LESS || node.token == LESSLESS) && node.args == NULL)
		return (1);
	return (0);
}

int	lx_cmdend(t_prompt curr)
{
	if (curr.token == AND || curr.token == OR || curr.token == PIPE)
		return (1);
	return (0);
}

t_prompt	*lx_setnext(t_prompt *old, t_prompt *new)
{
	if (old && old->token == CMD)
		old->next_cmd = new;
	return (new);
}

t_prompt	*lx_parent(t_prompt *curr, t_prompt *parent)
{
	if (!lx_argcheck(*curr))
		return (parent);
	return (curr);
}

void	lx_free_tokens(t_prompt *lst)
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
