/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk03.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:43:38 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/07 15:57:28 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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
