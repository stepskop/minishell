/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils005.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:27:59 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/16 12:33:22 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	remove backslashes
*	sh_rmbs returns a copy of arg string without backslashes
*/
char	*sh_rmbs(char *arg)
{
	char	*str[2];
	size_t	idx[2];

	if (!arg)
		return (NULL);
	str[0] = (char *) malloc ((ft_strlen (arg) + 1) * sizeof (char));
	if (!str[0])
		return (perror("malloc"), NULL);
	idx[0] = 0;
	idx[1] = 0;
	while (arg[idx[0]])
	{
		if (arg[idx[0]] == '\\')
		{
			idx[0]++;
			str[0][idx[1]] = arg[idx[0]];
		}
		else
			str[0][idx[1]] = arg[idx[0]];
		idx[0]++;
		idx[1]++;
	}
	str[0][idx[1]] = '\0';
	str[1] = ft_strdup (str[0]);
	return (free (str[0]), str[1]);
}

char	**sh_rmbs_args(char **args)
{
	char	**arg;
	char	*tmp;

	arg = args;
	while (*arg)
	{
		tmp = *arg;
		*arg = sh_rmbs (tmp);
		free (tmp);
		arg++;
	}
	return (args);
}

char	**sh_ud_rmbs(char **args)
{
	return (sh_rmbs_args (sh_uq_args (args)));
}
