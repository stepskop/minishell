/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:00:19 by username          #+#    #+#             */
/*   Updated: 2024/12/04 20:00:40 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_prompt	*lx_add(t_token token, t_prompt *prev, char *val)
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
	new->cmd = NULL;
	new->in_fd = 0;
	new->out_fd = 1;
	return (new);
}

static t_prompt	*lx_init(char *first)
{
	t_prompt	*lst;
	t_token	token;

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

int	lx_cmdend(t_prompt curr)
{
	if (curr.token == AND || curr.token == OR || curr.token == PIPE)
		return (1);
	return (0);
}

static t_prompt	*lx_create(char **cmd_raw, t_prompt *lst)
{
	t_prompt	*curr;
	t_prompt	*l_cmd;
	int			i;

	i = 0;
	curr = lst;
	l_cmd = curr;
	while (cmd_raw[++i])
	{
		if (lx_get_token(cmd_raw[i]) == WORD && !lx_cmdend(*curr))
		{
			if (!lx_add_arg(put_env(cmd_raw[i]), &lx_parent(curr, l_cmd)->args))
				return (lx_free_tokens(lst), NULL);
		}
		else
		{
			curr->next = lx_add(lx_get_token(cmd_raw[i]), curr, cmd_raw[i]);
			if (!curr->next)
				return (lx_free_tokens(lst), NULL);
			if (curr->next->token == CMD)
				l_cmd = curr->next;
			curr = curr->next;
		}
	}
	return (lst);
}

t_prompt	*lexer(char **cmd_raw)
{
	int			i;
	t_prompt		*lst;

	i = 0;
	lst = lx_init(cmd_raw[i]);
	if (!lst)
		return (NULL);
	lst = lx_create(cmd_raw, lst);
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
		printf("ITEM: %s, TOKEN: %i\n", curr->str_val, curr->token);
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
		curr = curr->next;
	}
	printf("------LEXER DBG END-------\n");
}
