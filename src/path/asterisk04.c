/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk04.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:43:38 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/25 13:10:17 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path.h"
#include "asterisk.h"

int	wildcard_check(char *wildcard, char *str)
{
	t_list	*parts[2];
	int		fisrt;

	parts[0] = a_split (wildcard, '*');
	parts[1] = parts[0];
	fisrt = 1;
	while (parts[1] && ft_strchr (parts[1]->content, '*'))
	{
		str = patern_prefix (str, (char *)(parts[1]->content), fisrt);
		if (!str)
			return (ft_lstclear (&parts[0], &a_split_clear), 0);
		parts[1] = parts[1]->next;
		fisrt = 0;
	}
	if (parts[1] && patern_suffix (str, parts[1]->content))
		return (ft_lstclear (&parts[0], &a_split_clear), 0);
	ft_lstclear (&parts[0], &a_split_clear);
	return (1);
}

char	*patern_prefix(char *str, char *prefix, int first)
{
	size_t	len[2];
	char	*str_;
	char	*prefix_;

	if (!str || !prefix)
		return (0);
	prefix_ = sh_remove_last_c (ft_strdup (prefix), '*');
	if (!prefix_)
		return (NULL);
	len[0] = sh_strlen(str);
	len[1] = sh_strlen(prefix_);
	if (len[1] > len[0])
		return (free (prefix_), NULL);
	if (first)
	{
		if (ft_strncmp(str, prefix_, len[1]))
			return (free (prefix_), NULL);
		else
			return (free (prefix_), str + len[1]);
	}
	str_ = ft_strnstr (str, prefix_, len[0]);
	if (!str_)
		return (free (prefix_), NULL);
	return (free (prefix_), str_ + len[1]);
}

int	patern_suffix(const char *str, const char *suffix)
{
	size_t	len[2];
	int		result;

	if (!str || !suffix)
		return (0);
	len[0] = sh_strlen(str);
	len[1] = sh_strlen(suffix);
	if (len[1] > len[0])
		return (1);
	result = ft_strncmp(str + len[0] - len[1], suffix, len[1]);
	return (result);
}
