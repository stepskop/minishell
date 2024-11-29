/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils003.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:27:59 by ksorokol          #+#    #+#             */
/*   Updated: 2024/11/29 05:42:21 by ksorokol         ###   ########.fr       */
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
