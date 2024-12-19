/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:06:47 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/19 21:35:59 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
*	check_quot checks for quotation at begin and end of string
*	return 
*	1 if ' 
*	2 if " 
*	0 otherwise
*/
int	check_quot(char *str)
{
	size_t	end;

	end = ft_strlen (str) - 1;
	if (str[0] == '\'' && str[0] == str[end])
		return (1);
	if (str[0] == '"' && str[0] == str[end])
		return (2);
	return (0);
}

/*
*	del_quot creats a new string without quotation at begin and end
*/
char	*del_quot(char *str)
{
	size_t	len;
	char	*new_str;

	if (!str)
		return (NULL);
	if (!check_quot (str))
		return (ft_strdup (str));
	len = ft_strlen (str) - 2;
	new_str = (char *) malloc ((len + 1) * sizeof (char));
	new_str[len] = '\0';
	ft_memcpy (new_str, &str[1], len);
	return (new_str);
}
