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

t_token	get_token(char *str)
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
	else if (ft_strcmp(str, "$?") == 0)
		return (LAST_STATUS);
	else
		return (WORD);
}

void	free_tokens(t_prompt *lst);

t_prompt	*lexer(char **cmd_raw, char **envp)
{
	int			i;
	t_prompt	*lst;
	t_prompt	*curr;
	t_token		token;

	i = 0;
	token = get_token(cmd_raw[i]);
	if (token == AND || token == OR || token == PIPE)
		return(sh_err("syntax error near unexpected token"), NULL);
	lst = lex_add(token, NULL);
	if (!lst)
		return (NULL);
	if (token == WORD)
		lst->token = CMD;
	lst->prev = NULL;
	curr = lst;
	while (cmd_raw[++i])
	{
		token = get_token(cmd_raw[i]);
		if (token == WORD && curr->token == CMD)
		{
			if (!add_arg(cmd_raw[i], &curr->args))
				return (free_tokens(lst), NULL);
		}
		else
			curr->next = lex_add(token, curr);
	}
	return (lst);
}
