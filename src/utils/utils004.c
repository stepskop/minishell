/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils004.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:27:59 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/28 23:23:10 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "_malloc_.h"

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

char	*sh_unquotes(char *arg)
{
	char	*str;
	char	c[2];
	size_t	idx[2];

	if (!arg)
		return (NULL);
	str = (void *) _malloc_ ((ft_strlen (arg) + 1) * sizeof (char));
	if (!str)
		return (NULL);
	idx[0] = 0;
	idx[1] = 0;
	c[0] = '\0';
	while (arg[idx[0]])
	{
		if (sh_bsq (arg, idx[0]) || (c[0] && c[0] != arg[idx[0]]))
			idx[1] = sh_setchstr (str, idx[1], arg, idx[0]) + 1;
		else if (c[0])
			c[0] = '\0';
		else
			c[0] = arg[idx[0]];
		idx[0]++;
	}
	str[idx[1]] = '\0';
	return (str);
}

/*
*	backslash after quote
*	sh_bsq returns 0 if befor quote char isn't backslash
*/
char	sh_bsq(char *arg, size_t idx)
{
	size_t	idx_;
	int		i;

	if (arg[idx] == '\'' || arg[idx] == '"')
	{
		i = 0;
		if (idx > 0)
		{
			idx_ = idx - 1;
			while (1)
			{
				if (arg[idx_] != '\\')
					break ;
				i = (i + 1) % 2;
				if (!idx_)
					break ;
				idx_--;
			}
		}
		if (i)
			return (arg[idx]);
		else
			return (0);
	}
	return (arg[idx]);
}

char	**sh_uq_args(char **args)
{
	char	**arg;
	char	*tmp;

	arg = args;
	if (!arg)
		return (NULL);
	while (*arg)
	{
		tmp = *arg;
		*arg = sh_unquotes (tmp);
		free (tmp);
		arg++;
	}
	return (args);
}

char	*sh_strtrim(char *s1, char *set)
{
	char	*str;

	str = ft_strtrim (s1, set);
	free (s1);
	return (str);
}
