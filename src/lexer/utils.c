/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:15:35 by username          #+#    #+#             */
/*   Updated: 2024/11/27 19:15:15 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_arg(char *str, t_args **args)
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

t_prompt *lex_add(t_token token, t_prompt *prev)
{
	t_prompt	*new;

	new = malloc(sizeof(t_prompt));
	if (!new)
		return (perror(NULL), NULL);
	new->token = token;
	new->next = NULL;
	new->prev = prev;
	new->cmd = NULL;
	new->args = NULL;
	return (new);
}
