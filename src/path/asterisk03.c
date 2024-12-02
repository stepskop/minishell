/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk03.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:43:38 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/02 17:53:30 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*aster_slash(char *pattern)
{
	t_list	*plst;
	char	*pathes[2];

	plst = NULL;
	pathes[0] = ft_strdup (pattern);
	pathes[1] = ft_strdup (pattern);
	ft_lstadd_back (&plst, ft_lstnew (sh_new_de(DT_DIR, "", pathes)));
	sh_del_arr ((void **)pathes, 2);
	return (plst);
}

t_list	*aster_dot(char *pattern)
{
	t_list	*plst;
	char	*pathes[2];

	plst = NULL;
	pathes[0] = ft_strdup (pattern);
	pathes[1] = sh_replace_dot (pattern);
	ft_lstadd_back (&plst, ft_lstnew (sh_new_de (DT_DIR, pattern, pathes)));
	sh_del_arr ((void **)pathes, 2);
	return (plst);
}

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

int	check_d_type(t_list *dir)
{
	if (((t_de *) dir->content)->d_type == DT_DIR
		|| ((t_de *) dir->content)->d_type == DT_LNK)
		return (1);
	return (0);
}
