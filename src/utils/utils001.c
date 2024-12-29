/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils001.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:27:59 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/28 23:22:19 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "_malloc_.h"

size_t	sh_strlen(const char *s)
{
	size_t	idx;

	if (!s)
		return (0);
	idx = 0;
	while (s[idx])
		idx++;
	return (idx);
}

int	sh_check_eol(char *cmd)
{
	size_t			idx;
	unsigned int	single_quote;
	unsigned int	double_quote;

	if (!cmd)
		return (1);
	single_quote = 0;
	double_quote = 0;
	idx = 0;
	while (cmd[idx])
	{
		if (cmd[idx] == '\'' && !(double_quote % 2))
			if (idx == 0 || (idx > 0 && cmd[idx - 1] != '\\'))
				single_quote++;
		if (cmd[idx] == '"' && !(single_quote % 2))
			if (idx == 0 || (idx > 0 && cmd[idx - 1] != '\\'))
				double_quote++;
		idx++;
	}
	if (!(single_quote % 2) && !(double_quote % 2))
		return (1);
	return (0);
}

int	sh_backslash(char **line)
{
	char	*str;
	size_t	idx[2];
	int		result;

	str = (char *) _malloc_ (sh_strlen (*line) + 1);
	if (!str)
		return (0);
	idx[0] = 0;
	idx[1] = 0;
	result = 0;
	while ((*line)[idx[0]])
	{
		if (((*line)[idx[0]] == '\\') && ((*line)[idx[0] + 1] == '\0'))
		{
			result = 1;
			break ;
		}
		str[idx[1]] = (*line)[idx[0]];
		idx[0]++;
		idx[1]++;
	}
	str[idx[1]] = '\0';
	return (free (*line), *line = str, result);
}

char	*sh_strdup(char *str)
{
	if (!str)
		return (NULL);
	return (ft_strdup (str));
}

void	sh_ppfree(char	**pp)
{
	char	**pp_;

	if (!pp)
		return ;
	pp_ = pp;
	while (*pp_)
	{
		free (*pp_);
		pp_++;
	}
	free (pp);
}
