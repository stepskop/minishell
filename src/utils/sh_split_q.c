/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_split_q.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:27:59 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/06 15:42:14 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*sh_split_map(char *str, char c);
static int	sh_split_couont(char *map, size_t len);
static char	*sh_split_element(char *map, size_t len, int elem);

char	**sh_split_q(char *str, char c)
{
	char	*map;
	char	**result;
	int		counter;
	int		idx;

	map = sh_split_map (str, c);
	if (!map)
		return (NULL);
	counter = sh_split_couont(map, ft_strlen (str));
	result = (char **) malloc ((counter + 1) * sizeof (char **));
	if (!result)
		return (free (map), NULL);
	idx = 0;
	while (idx < counter)
	{
		result[idx] = sh_split_element (map, ft_strlen (str), idx + 1);
		idx++;
	}
	result[counter] = NULL;
	free (map);
	return (result);
}

static char	*sh_split_map(char *str, char c)
{
	char	*map;
	size_t	idx;
	char	qc;

	map = (char *) malloc ((ft_strlen (str) + 1) * sizeof (char));
	if (!map)
		return (NULL);
	idx = 0;
	qc = 0;
	while (str[idx])
	{
		if (!qc && (str[idx] == '"' || str[idx] == '\''))
			qc = str[idx];
		else if (qc && str[idx] == qc)
			qc = 0;
		if (!qc && str[idx] == c)
			map[idx] = 0;
		else
			map[idx] = str[idx];
		idx++;
	}
	map[idx] = 0;
	return (map);
}

static int	sh_split_couont(char *map, size_t len)
{
	size_t	idx;
	int		counter;
	int		element;

	counter = 0;
	idx = 0;
	element = 0;
	while (idx <= len)
	{
		if (!element && map[idx])
			element = 1;
		if (element && !map[idx])
		{
			element = 0;
			counter++;
		}
		idx++;
	}
	return (counter);
}

static char	*sh_split_element(char *map, size_t len, int elem)
{
	size_t	idx;
	char	*result;
	int		counter;
	int		element;

	counter = 0;
	element = 0;
	idx = 0;
	while (idx <= len)
	{
		if (!element && map[idx])
		{
			element = 1;
			counter++;
			if (counter == elem)
				break ;
		}
		if (element && !map[idx])
			element = 0;
		idx++;
	}
	result = ft_strdup (&map[idx]);
	return (result);
}
