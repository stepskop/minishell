/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils002.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 00:26:09 by username          #+#    #+#             */
/*   Updated: 2024/12/06 00:28:25 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_prompt	*lx_add(t_token token, t_prompt *prev, char *val)
{
	t_prompt	*new;

	new = malloc(sizeof(t_prompt));
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
	return (new);
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
