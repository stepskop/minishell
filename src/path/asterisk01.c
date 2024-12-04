/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:43:38 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/04 16:22:31 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*sh_asterisk(char *astr)
{
	t_list	*dirs[5];
	char	*result;

	if (!astr)
		return (NULL);
	if ((astr[0] == '\'' && astr[ft_strlen (astr) - 1] == '\'')
		|| (astr[0] == '"' && astr[ft_strlen (astr) - 1] == '"')
		|| !ft_strchr (astr, '*'))
		return (ft_strdup (astr));
	dirs[0] = a_split (astr, '/');
	dirs[4] = NULL;
	dirs[3] = aster_start (dirs[0]);
	dirs[1] = get_dirs (dirs[3]->content);
	dirs[2] = dirs[1];
	while (dirs[2])
	{
		aster_recursion (dirs[2], dirs[3]->next, &dirs[4]);
		dirs[2] = dirs[2]->next;
	}
	ft_lstclear (&dirs[1], &dirs_clean);
	ft_lstclear (&dirs[0], &a_split_clear);
	aster_order (dirs[4]);
	result = sh_lst2str (dirs[4], ' ');
	ft_lstclear (&dirs[4], &a_split_clear);
	return (result);
}

t_list	*get_dirs(char *pattern)
{
	t_list	*result;
	char	*str[2];

	result = NULL;
	if (!pattern)
		return (NULL);
	else if (pattern[0] == '/')
		result = aster_slash (pattern);
	else if (pattern[0] == '.' && (pattern[0] == '/' || pattern[0] == '\0'))
		result = aster_dot (pattern);
	if (result)
		return (result);
	str[0] = ft_strdup ("");
	str[1] = get_sh_path(1);
	if (ft_strchr (pattern, '*'))
		get_lst_dirs (&result, pattern, str);
	else
	{
		sh_del_arr ((void **)str, 2);
		str[0] = ft_strdup (pattern);
		str[1] = ft_strdup (pattern);
		ft_lstadd_back (&result, ft_lstnew (sh_new_de(DT_DIR, pattern, str)));
	}
	return (sh_del_arr ((void **)str, 2), result);
}

int	get_lst_dirs(t_list **lst, char *pattern, char *pathes[])
{
	DIR				*dp;
	struct dirent	*ep;
	char			*pttrn;

	if (pattern[0] == '/' && pathes[1])
		return (2);
	pttrn = sh_remove_last_c (ft_strdup (pattern), '/');
	dp = opendir (pathes[1]);
	if (dp == NULL)
		return (free (pttrn), 0);
	ep = readdir (dp);
	while (ep)
	{
		if (dirs_check (ep->d_name, pttrn))
			ft_lstadd_back (lst, ft_lstnew (
					sh_new_de(ep->d_type, ep->d_name, pathes)));
		ep = readdir (dp);
	}
	(void) closedir (dp);
	return (free (pttrn), 1);
}

void	aster_recursion(t_list *dir, t_list *pttrns, t_list **result)
{
	t_list	*dirs[2];
	char	*pathes[2];

	if (pttrns)
	{
		dirs_init (dirs, pathes, dir);
		if (get_lst_dirs (&dirs[0], pttrns->content, pathes) == 2)
			return (aster_recursion (dir, pttrns->next, result));
		dirs[1] = dirs[0];
		while (dirs[1])
		{
			aster_recursion (dirs[1], pttrns->next, result);
			dirs[1] = dirs[1]->next;
		}
		ft_lstclear (&dirs[0], &dirs_clean);
		sh_del_arr ((void **) pathes, 2);
	}
	else
		ft_lstadd_back (result, ft_lstnew
			(ft_strdup (((t_de *) dir->content)->rel_name)));
}

int	wildcard_check(char *wildcard, char *str)
{
	t_list	*parts[2];
	char	*part[3];

	part[1] = str;
	parts[0] = a_split (wildcard, '*');
	parts[1] = parts[0];
	while (parts[1])
	{
		part[0] = ft_strdup(parts[1]->content);
		part[0] = sh_remove_last_c (part[0], '*');
		part[2] = ft_strnstr (part[1], part[0], ft_strlen (part[1]));
		if (part[1] != part[2])
			return (ft_lstclear (&parts[0], &a_split_clear), free (part[0]), 0);
		part[1] += ft_strlen (part[0]);
		free (part[0]);
		parts[1] = parts[1]->next;
	}
	if (ft_strlen (part[1]) > 0
		&& wildcard[ft_strlen (wildcard) - 1] != '*')
		return (ft_lstclear (&parts[0], &a_split_clear), 0);
	ft_lstclear (&parts[0], &a_split_clear);
	return (1);
}
