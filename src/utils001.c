/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils001.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:27:59 by ksorokol          #+#    #+#             */
/*   Updated: 2024/11/20 23:59:28 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	sh_check_eol(char *cmmnd)
{
	size_t			idx;
	unsigned int	single_quote;
	unsigned int	double_quote;

	if (!cmmnd)
		return (1);
	single_quote = 0;
	double_quote = 0;
	idx = 0;
	while (cmmnd[idx])
	{
		if (cmmnd[idx] == '\'')
			single_quote++;
		if (cmmnd[idx] == '"')
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

	str = (char *) malloc (sh_strlen (*line) + 1);
	if (!str)
		return (0);
	idx[0] = 0;
	idx[1] = 0;
	result = 0;
	while ((*line)[idx[0]])
	{
		if ((*line)[idx[0]] == '\\')
			idx[0]++;
		if ((*line)[idx[0]] == '\0')
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

char	*sh_strjoin(char *s1, char *s2)
{
	char	*result;

	if (!s1)
	{
		s1 = (char *) malloc (1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s2)
	{
		s2 = (char *) malloc (1);
		if (!s2)
			return (NULL);
		s2[0] = '\0';
	}
	result = ft_strjoin (s1, s2);
	free (s1);
	free (s2);
	return (result);
}

void	sh_ppfree(char	**pp)
{
	char	**pp_;

	pp_ = pp;
	while (*pp_)
	{
		free (*pp_);
		pp_++;
	}
	free (pp);
}
