/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk04.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:43:38 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/02 19:03:04 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	aster_order(t_list *result)
{
	t_list	*lst[2];
	void	*buffer;
	int		i;

	lst[0] = result;
	while (lst[0] && lst[0]->next)
	{
		lst[1] = lst[0]->next;
		i = 0;
		while (lst[1])
		{
			if (aster_pathcmp (lst[0]->content, lst[1]->content) > 0)
			{
				buffer = lst[0]->content;
				lst[0]->content = lst[1]->content;
				lst[1]->content = buffer;
				lst[0] = lst[1];
				i = 1;
			}
			lst[1] = lst[1]->next;
		}
		if (i)
			lst[0] = result;
		else
			lst[0] = lst[0]->next;
	}
}

int	aster_pathcmp(char *path1, char *path2)
{
	t_list	*path[4];

	path[0] = a_split (path1, '/');
	path[1] = a_split (path2, '/');
	path[2] = path[0];
	path[3] = path[1];
	while (path[0] && path[1])
	{
		if (aster_strcmp (path[0]->content, path[1]->content) > 0)
		{
			ft_lstclear (&path[2], &a_split_clear);
			ft_lstclear (&path[3], &a_split_clear);
			return (1);
		}
		path[0] = path[0]->next;
		path[1] = path[1]->next;
	}
	ft_lstclear (&path[2], &a_split_clear);
	ft_lstclear (&path[3], &a_split_clear);
	return (0);
}

int	aster_strcmp(char *s1, char *s2)
{
	size_t	idx;
	char	c[2];

	idx = 0;
	while (s1[idx] && s2[idx])
	{
		c[0] = ft_tolower (s1[idx]);
		c[1] = ft_tolower (s2[idx]);
		if (c[0] != c[1])
			return (c[0] - c[1]);
		idx++;
	}
	if (s1[idx] == s2[idx])
		return (0);
	return (s1[idx] - s2[idx]);
}
