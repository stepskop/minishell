/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils004.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:27:59 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/15 16:50:14 by ksorokol         ###   ########.fr       */
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

char	*sh_unquotes(char *arg)
{
	char	*str;
	size_t	idx[2];

	if (!arg)
		return (NULL);
	str = (void *) malloc ((ft_strlen (arg) + 1) * sizeof (char));
	if (!str)
		return (NULL);
	idx[0] = 0;
	idx[1] = 0;
	while (arg[idx[0]])
	{
		if (sh_bsq (arg, idx[0]))
		{
			str[idx[1]] = arg[idx[0]];
			idx[1]++;
		}
		idx[0]++;
	}
	str[idx[1]] = '\0';
	return (str);
}

char	sh_bsq(char *arg, size_t idx)
{
	if (arg[idx] == '\'' || arg[idx] == '"')
	{
		if (idx > 0 && arg[idx - 1] == '\\')
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
	while (*arg)
	{
		tmp = *arg;
		*arg = sh_unquotes (tmp);
		free (tmp);
		arg++;
	}
	return (args);
}
