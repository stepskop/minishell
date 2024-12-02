/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:43:38 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/02 16:53:36 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*sh_asterisk(char *astr)
{
	t_list	*dirs[4];
	t_list	*result;

	if (!astr)
		return (NULL);
	if ((astr[0] == '\'' && astr[ft_strlen (astr) - 1] == '\'')
		|| (astr[0] == '"' && astr[ft_strlen (astr) - 1] == '"')
		|| !ft_strchr (astr, '*'))
		return (ft_lstnew (ft_strdup (astr)));
	dirs[0] = a_split (astr, '/');
	result = NULL;
	dirs[3] = aster_start (dirs[0]);
	dirs[1] = get_dirs (dirs[3]->content);
	dirs[2] = dirs[1];
	while (dirs[2])
	{
		aster_recursion (dirs[2], dirs[3]->next, &result);
		dirs[2] = dirs[2]->next;
	}
	ft_lstclear (&dirs[1], &dirs_clean);
	ft_lstclear (&dirs[0], &a_split_clear);
	aster_order (result);
	return (result);
}

t_list	*get_dirs(char *pattern)
{
	t_list	*result;
	char	*str[2];

	str[0] = NULL;
	str[1] = NULL;
	result = NULL;
	if (!pattern)
		return (NULL);
	else if (pattern[0] == '/')
		result = aster_slash (pattern);
	else if (pattern[0] == '~')
		result = aster_tilde (pattern);
	else if (pattern[0] == '.')
		result = aster_dot (pattern);
	if (result)
		return (result);
	if (ft_strchr (pattern, '*'))
		get_lst_dirs (&result, pattern, str);
	else
	{
		str[0] = ft_strdup (pattern);
		str[1] = ft_strdup (pattern);
		ft_lstadd_back (&result, ft_lstnew (sh_new_de(DT_DIR, pattern, str)));
	}
	return (result);
}

int	get_lst_dirs(t_list **lst, char *pattern, char *pathes[])
{
	DIR				*dp;
	struct dirent	*ep;
	char			*pttrn;

	if (pattern[0] == '/' && pathes[1])
		return (2);
	pttrn = sh_remove_last_c (ft_strdup (pattern), '/');
	if (!pathes[0])
	{
		pathes[0] = "";
		pathes[1] = get_sh_path(1);
	}
	dp = opendir (pathes[1]);
	if (dp == NULL)
		return (0);
	ep = readdir (dp);
	while (ep)
	{
		if (dirs_check (ep->d_name, pttrn, ep->d_type))
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
		if (check_d_type (dir))
		{
			dirs_init (dirs, pathes, dir);
			if (get_lst_dirs (&dirs[0], pttrns->content, pathes) == 2)
				return (aster_recursion (dir, pttrns->next, result));
			dirs[1] = dirs[0];
			while (dirs[1])
			{
				if (check_d_type (dirs[1]) || !pttrns->next)
					aster_recursion (dirs[1], pttrns->next, result);
				dirs[1] = dirs[1]->next;
			}
			ft_lstclear (&dirs[0], &dirs_clean);
			sh_del_arr ((void **) pathes, 2);
		}
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
		return (0);
	ft_lstclear (&parts[0], &a_split_clear);
	return (1);
}
