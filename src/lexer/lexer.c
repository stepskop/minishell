/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:00:19 by username          #+#    #+#             */
/*   Updated: 2024/11/27 19:27:44 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_prompt	*lex_add(t_token token, t_prompt *prev, char *val)
{
	t_prompt	*new;

	new = malloc(sizeof(t_prompt));
	if (!new)
		return (perror(NULL), NULL);
	new->token = token;
	if (token == WORD)
		new->token = CMD;
	new->next = NULL;
	new->prev = prev;
	new->args = NULL;
	new->str_val = val;
	return (new);
}

static t_prompt	*lex_init(char *first)
{
	t_prompt	*lst;
	t_token	token;

	token = lx_get_token(first);
	if (token == AND || token == OR || token == PIPE)
		return (sh_err("syntax error near unexpected token"), NULL);
	lst = lex_add(token, NULL, first);
	if (!lst)
		return (NULL);
	if (token == WORD)
		lst->token = CMD;
	lst->prev = NULL;
	return (lst);
}

t_prompt	*lexer(char **cmd_raw)
{
	int			i;
	t_prompt		*lst;
	t_prompt		*curr;

	i = 0;
	lst = lex_init(cmd_raw[i]);
	if (!lst)
		return (NULL);
	curr = lst;
	while (cmd_raw[++i])
	{
		if (lx_get_token(cmd_raw[i]) == WORD && lx_accept_sub(*curr))
		{
			if (!lx_add_arg(put_env(cmd_raw[i]), &curr->args))
				return (lx_free_tokens(lst), NULL);
		}
		else
		{
			curr->next = lex_add(lx_get_token(cmd_raw[i]), curr, cmd_raw[i]);
			if (!curr->next)
				return (lx_free_tokens(lst), NULL);
			curr = curr->next;
		}
	}
	return (lst);
}

void	print_lex_dbg(t_prompt *lst)
{
	printf("------LEXER DBG-------\n");
	while (lst)
	{
		printf("ITEM: %s, TOKEN: %i\n", lst->str_val, lst->token);
		if (lst->args)
		{
			while (lst->args)
			{
				printf("\tSUB_ARG: %s\n", lst->args->data);
				lst->args = lst->args->next;
			}
		}
		lst = lst->next;
	}
	printf("------LEXER DBG END-------\n");
}
