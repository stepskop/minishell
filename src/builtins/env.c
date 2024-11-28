/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:41:06 by ksorokol          #+#    #+#             */
/*   Updated: 2024/11/27 13:43:52 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(char **envp)
{
	char	**list;

	list = envp;
	while (*list)
	{
		write (1, *list, ft_strlen (*list));
		write (1, "\n", 1);
		list++;
	}
}
