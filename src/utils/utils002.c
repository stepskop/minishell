/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils002.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:27:59 by ksorokol          #+#    #+#             */
/*   Updated: 2024/11/26 12:21:55 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*sh_strcat(char *s1, char *s2)
{
	char	*result;
	size_t	len;

	len = ft_strlen (s1) + ft_strlen (s2) + 1;
	result = (char *) malloc (len * sizeof (char));
	if (!result)
		return (NULL);
	ft_memcpy (result, s1, ft_strlen (s1));
	ft_memcpy (&result[ft_strlen (s1)], s2, ft_strlen (s2));
	result[len - 1] = '\0';
	return (result);
}
