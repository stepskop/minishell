/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:34:46 by username          #+#    #+#             */
/*   Updated: 2024/12/19 21:58:06 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_args(t_args *args)
{
	t_args	*tmp;

	while (args)
	{
		tmp = args->next;
		free(args->data);
		free(args);
		args = tmp;
	}
}

void	free_prompt(t_prompt *lst)
{
	t_prompt	*curr;
	t_prompt	*tmp;

	curr = lst;
	while (curr)
	{
		tmp = curr->next;
		free_args(curr->args);
		free(curr->str_val);
		free(curr);
		curr = tmp;
	}
}
