/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk03.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:43:38 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/01 19:48:37 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*aster_slash(char *pattern)
{
	t_list	*plst;
	char	*pathes[2];

	plst = NULL;
	pathes[0] = ft_strdup ("");
	pathes[1] = ft_strdup (pathes[0]);
	ft_lstadd_back (&plst, ft_lstnew (sh_new_de(DT_DIR, pattern, pathes)));
	sh_del_arr ((void **)pathes, 2);
	return (plst);
}


// aster_tilde may not be needed - if we replace '~' before in parsing args for CMD
t_list	*aster_tilde(char *pattern)
{
	t_list	*plst;
	char	*pathes[2];

	plst = NULL;
	if (pattern[1] == '/' || pattern[1] == '\0')
	{
		pathes[0] = ft_strdup (getenv ("HOME"));
		pathes[1] = ft_strdup (pathes[0]);
		ft_lstadd_back (&plst, ft_lstnew (sh_new_de (DT_DIR, "", pathes)));
		sh_del_arr ((void **)pathes, 2);
	}
	return (plst);
}

t_list	*aster_dot(char *pattern)
{
	t_list	*plst;
	char	*pathes[2];

	plst = NULL;
	if (pattern[1] == '/' || pattern[1] == '\0')
	{
		pathes[0] = ft_strdup ("");
		pathes[1] = get_sh_path (1);
		ft_lstadd_back (&plst, ft_lstnew (sh_new_de (DT_DIR, pattern, pathes)));
		sh_del_arr ((void **)pathes, 2);
	}
	return (plst);
}
