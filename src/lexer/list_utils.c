/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 00:26:09 by username          #+#    #+#             */
/*   Updated: 2024/12/29 14:33:14 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "_malloc_.h"

t_prompt	*lx_add(t_token token, t_prompt *prev, char *val)
{
	t_prompt	*new;

	new = _malloc_(sizeof(t_prompt));
	if (!new)
		return (perror(NULL), NULL);
	new->token = token;
	if (token == WORD)
		new->token = CMD;
	new->next = NULL;
	new->next_cmd = NULL;
	new->prev = prev;
	new->args = NULL;
	new->str_val = val;
	new->cmd = NULL;
	new->in_fd = 0;
	new->out_fd = 1;
	new->proc_less = 0;
	new->io_err = 0;
	return (new);
}

static int	lx_add_arg(char *str, t_args **args)
{
	t_args	*new;
	t_args	*curr;

	new = _malloc_(sizeof(t_args));
	if (!new)
		return (0);
		// return (perror("_malloc_"), 0);
	new->data = str;
	new->next = NULL;
	if (!*args)
		return (*args = new, 1);
	curr = *args;
	while (curr && curr->next)
		curr = curr->next;
	curr->next = new;
	return (1);
}

t_token	lx_get_token(char *str)
{
	if (ft_strcmp(str, "<") == 0)
		return (LESS);
	else if (ft_strcmp(str, "<<") == 0)
		return (LESSLESS);
	else if (ft_strcmp(str, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(str, "||") == 0)
		return (OR);
	else if (ft_strcmp(str, "&&") == 0)
		return (AND);
	else if (ft_strcmp(str, ">") == 0)
		return (GREAT);
	else if (ft_strcmp(str, ">>") == 0)
		return (GREATGREAT);
	else
		return (WORD);
}

int	lx_parse(char *str, t_prompt **curr, t_prompt **l_par, t_prompt **l_cmd)
{
	if (lx_get_token(str) == WORD && !lx_cmdend(**curr))
	{
		if (!lx_argcheck(**l_par))
			if (!lx_setlastcmd(l_par, l_cmd, curr, str))
				return (1);
		if (!lx_add_arg(str, &(*l_par)->args))
			return (0);
	}
	else
	{
		(*curr)->next = lx_add(lx_get_token(str), *curr, str);
		if (!(*curr)->next)
			return (0);
		if (lx_argcheck(*(*curr)->next))
			*l_par = (*curr)->next;
		if ((*curr)->next->token == CMD)
		{
			if (*l_cmd)
				(*l_cmd)->next_cmd = (*curr)->next;
			*l_cmd = (*curr)->next;
		}
		*curr = (*curr)->next;
	}
	return (1);
}
