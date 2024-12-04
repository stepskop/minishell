/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:15:35 by username          #+#    #+#             */
/*   Updated: 2024/11/28 17:37:20 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	lx_add_arg(char *str, t_args **args)
{
	t_args	*new;
	t_args	*curr;

	new = malloc(sizeof(t_args));
	if (!new)
		return (perror("malloc"), 0);
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

int	lx_accept_sub(t_prompt node)
{
	if (node.token == CMD)
		return (1);
	else if ((node.token == GREAT || node.token == GREATGREAT || \
		node.token == LESS || node.token == LESSLESS) && node.args == NULL)
		return (1);
	return (0);
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
		free(curr);
		curr = tmp;
	}
}
