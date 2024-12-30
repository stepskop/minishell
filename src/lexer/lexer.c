/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:00:19 by username          #+#    #+#             */
/*   Updated: 2024/12/30 01:00:11 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_prompt	*lx_init(char *first)
{
	t_prompt	*lst;
	t_token		token;

	token = lx_get_token(first);
	if (token == AND || token == OR || token == PIPE)
		return (sh_err("syntax error near unexpected token"), NULL);
	lst = lx_add(token, NULL, first);
	if (!lst)
		return (NULL);
	if (token == WORD)
		lst->token = CMD;
	lst->prev = NULL;
	return (lst);
}

static t_prompt	*lx_create(char **cmd_raw, t_prompt *lst)
{
	t_prompt	*curr;
	t_prompt	*last_cmd;
	t_prompt	*last_par;
	int			i;

	i = 0;
	curr = lst;
	last_cmd = NULL;
	last_par = curr;
	if (last_par->token == CMD)
		last_cmd = last_par;
	while (cmd_raw[++i])
	{
		if (!lx_parse(cmd_raw[i], &curr, &last_par, &last_cmd))
			return (free_prompt(lst), NULL);
		if (!curr)
			return (free_prompt(lst), NULL);
	}
	return (lst);
}

t_prompt	*lexer(char **cmd_raw)
{
	int			i;
	t_prompt	*lst;

	i = 0;
	lst = lx_init(cmd_raw[i]);
	if (!lst)
		return (sh_ppfree(cmd_raw), NULL);
	lst = lx_create(cmd_raw, lst);
	free(cmd_raw);
	return (lst);
}

void	print_lex_dbg(t_prompt *lst)
{
	t_prompt	*curr;
	t_args		*curr_arg;

	curr = lst;
	printf("------LEXER DBG-------\n");
	while (curr)
	{
		printf("[%p]\n", curr);
		printf("ITEM: %s, TOKEN: %i, NEXT_CMD: %p\n", curr->str_val,
			curr->token, curr->next_cmd);
		printf("IN: %d, OUT: %d\n", curr->in_fd, curr->out_fd);
		curr_arg = curr->args;
		if (curr_arg)
		{
			while (curr_arg)
			{
				printf("\tSUB_ARG: %s\n", curr_arg->data);
				curr_arg = curr_arg->next;
			}
		}
		printf("\n\n\n");
		curr = curr->next;
	}
	printf("------LEXER DBG END-------\n");
}
