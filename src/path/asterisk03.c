/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk03.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:43:38 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/25 12:11:03 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path.h"
#include "asterisk.h"

/*
*	aster_slash returns a start dir or dirs if a path starts with / (slash)
*/
// t_list	*aster_slash(char *pattern)
// {
// 	t_list	*plst;
// 	char	*pathes[2];

// 	plst = NULL;
// 	pathes[0] = ft_strdup (pattern);
// 	pathes[1] = ft_strdup (pattern);
// 	ft_lstadd_back (&plst, ft_lstnew (sh_new_de(DT_DIR, "", pathes)));
// 	sh_del_arr ((void **)pathes, 2);
// 	return (plst);
// }

/*
*	aster_dot returns a start dir or dirs if a path starts with . (dot)
*/
// t_list	*aster_dot(char *pattern)
// {
// 	t_list	*plst;
// 	char	*pathes[2];

// 	plst = NULL;
// 	pathes[0] = ft_strdup (pattern);
// 	pathes[1] = sh_replace_dot (pattern);
// 	ft_lstadd_back (&plst, ft_lstnew (sh_new_de (DT_DIR, pattern, pathes)));
// 	sh_del_arr ((void **)pathes, 2);
// 	return (plst);
// }

/*
*	aster_other returns a start dir or dirs for not / (slash) or . (dot)
*/
// t_list	*aster_other(char *pattern)
// {
// 	t_list	*plst;
// 	char	*pathes[2];

// 	plst = NULL;
// 	pathes[0] = ft_strdup (pattern);
// 	pathes[1] = sh_replace_dot ("");
// 	ft_lstadd_back (&plst, ft_lstnew (sh_new_de (DT_DIR, pattern, pathes)));
// 	free (pathes[0]);
// 	return (plst);
// }

/*
*	aster_start joins all dirs in linked list (path) before met *
*/
t_list	*aster_start(t_list *dirs)
{
	t_list	*dirs_[2];
	char	*dir;

	dirs_[0] = dirs;
	dirs_[1] = NULL;
	dir = (char *)(dirs_[0])->content;
	while (dirs_[0]->next && !ft_strchr (dir, '*'))
	{
		if (dirs_[1])
			(dirs_[0])->content = sh_strjoin_free
				((dirs_[1])->content, (dirs_[0])->content, 2);
		dirs_[1] = dirs_[0];
		dirs_[0] = (dirs_[0])->next;
		dir = (char *)(dirs_[0])->content;
	}
	if (!dirs_[1])
		return (dirs);
	return (dirs_[1]);
}

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
