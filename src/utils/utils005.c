/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils005.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:27:59 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/19 21:35:34 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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

int	sh_insq(char *arg, size_t pos)
{
	size_t	idx;
	int		i[2];

	idx = 0;
	i[0] = 0;
	i[1] = 0;
	while (idx < pos)
	{
		if (arg[idx] == '"' && !sh_bsq (arg, idx))
			i[0] = (i[0] + 1) % 2;
		if (arg[idx] == '\'' && !sh_bsq (arg, idx) && !i[0])
			i[1] = (i[1] + 1) % 2;
		idx++;
	}
	return (i[1]);
}

size_t	sh_setchstr(char *str_d, size_t idx_d, char *str_s, size_t idx_s)
{
	if (!str_d || !str_s)
		return (0);
	str_d[idx_d] = str_s[idx_s];
	return (idx_d);
}
