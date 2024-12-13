/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils004.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:27:59 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/13 13:48:15 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sh_pstr_size(char **pstr)
{
	char	**idx;
	int		result;

	result = 0;
	idx = pstr;
	while (*idx)
	{
		result++;
		idx++;
	}
	return (result);
}