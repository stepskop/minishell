/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:00:57 by username          #+#    #+#             */
/*   Updated: 2024/11/28 17:38:25 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_input	*process_node(t_input *old, t_input *new, t_input **lst)
{
	if (old)
	{
		free_args(old->args);
		free(old);
	}
	if (!new->prev)
	{
		*lst = new->next;
		new->next->prev = NULL;
	}
	return (new);
}

static int	ex_check_infile(t_input **lst)
{
	t_input	*input_node;
	t_input	*curr;

	input_node = NULL;
	curr = *lst;
	while (curr)
	{
		if (curr->token == LESS || curr->token == LESSLESS)
		{
			input_node = process_node(input_node, curr, lst);
		}
		curr = curr->next;
	}
	if (!input_node)
		return (0);
	return (1);
}

void	executor(t_input *lst)
{
	int		infile_fd;
	t_input	*curr;

	infile_fd = ex_check_infile(&lst);
	curr = lst;
	while (curr)
	{

	}
}
