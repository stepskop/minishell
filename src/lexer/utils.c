/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:15:35 by username          #+#    #+#             */
/*   Updated: 2024/12/27 04:47:31 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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

int	lx_setlastcmd(t_prompt **last_par, t_prompt **last_cmd,
	t_prompt **curr, char *str)
{
	while (*last_par && (*last_par)->token != CMD)
	{
		*last_par = (*last_par)->prev;
		if (*last_par && (*last_par)->token == PIPE)
			*last_par = NULL;
	}
	if (*last_par)
		return (1);
	(*curr)->next = lx_add(WORD, *curr, str);
	if (!(*curr)->next)
		return (0);
	*last_par = (*curr)->next;
	if (*last_cmd)
		(*last_cmd)->next_cmd = (*curr)->next;
	*last_cmd = (*curr)->next;
	*curr = (*curr)->next;
	return (0);
}
