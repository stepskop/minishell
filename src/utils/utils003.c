/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils003.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:27:59 by ksorokol          #+#    #+#             */
/*   Updated: 2024/11/30 17:45:23 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*sh_strcat_free(char *s1, char *s2, int opt)
{
	char	*result;

	result = sh_strcat (s1, s2);
	if (opt == 1)
		free (s1);
	else if (opt == 2)
		free (s2);
	else if (opt == 3)
	{
		free (s1);
		free (s2);
	}
	return (result);
}

void	sh_del_arr(void *arr[], int arr_size)
{
	int	idx;

	idx = 0;
	while (idx < arr_size)
	{
		free (arr[idx]);
		idx++;
	}
}
