/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:34:46 by username          #+#    #+#             */
/*   Updated: 2024/11/28 17:36:12 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args(t_args *args)
{
	t_args	*tmp;

	while (args)
	{
		tmp = args->next;
		free(args);
		args = tmp;
	}
}
