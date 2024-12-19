/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk04.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:43:38 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/19 21:50:48 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path.h"
#include "asterisk.h"

/*
*	aster_order is sorting linked list of pathes by ASCII ...
*/
void	aster_order(t_list *result)
{
	t_list	*lst[3];
	void	*buffer;
	int		i[2];

	i[0] = ft_lstsize (result);
	lst[1] = ft_lstlast (result);
	while (i[0] > 0)
	{
		lst[0] = result;
		while (lst[0] != lst[1])
		{
			i[1] = aster_pathcmp (lst[0]->content, lst[0]->next->content);
			if (i[1] > 0)
			{
				buffer = lst[0]->next->content;
				lst[0]->next->content = lst[0]->content;
				lst[0]->content = buffer;
			}
			lst[2] = lst[0];
			lst[0] = lst[0]->next;
		}
		lst[1] = lst[2];
		i[0]--;
	}
}

/*
*	aster_pathcmp compares each dir in a pathes one by one
*/
int	aster_pathcmp(char *path1, char *path2)
{
	t_list	*path[4];
	int		i;

	path[0] = a_split (path1, '/');
	path[1] = a_split (path2, '/');
	path[2] = path[0];
	path[3] = path[1];
	while (path[0] && path[1])
	{
		i = ft_strcmp (path[0]->content, path[1]->content);
		if (i != 0)
		{
			return (ft_lstclear (&path[2], &a_split_clear),
				ft_lstclear (&path[3], &a_split_clear), i);
		}
		path[0] = path[0]->next;
		path[1] = path[1]->next;
	}
	ft_lstclear (&path[2], &a_split_clear);
	ft_lstclear (&path[3], &a_split_clear);
	return (0);
}
