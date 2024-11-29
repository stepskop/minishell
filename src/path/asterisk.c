/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:43:38 by ksorokol          #+#    #+#             */
/*   Updated: 2024/11/29 06:16:21 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*sh_asterisk(char *astr)
{
	t_list	*dirs;
	t_list	*result;
	char	*path;

	if (!astr)
		return (NULL);
	if ((astr[0] == '\'' && astr[ft_strlen (astr) - 1] == '\'')
		|| (astr[0] == '"' && astr[ft_strlen (astr) - 1] == '"')
		|| !ft_strchr (astr, '*'))
		return (ft_lstnew (ft_strdup (astr)));
	dirs = a_split (astr, '/');
	path = NULL;
	result = NULL;
	get_aster_dir (path, dirs, &result);
	ft_lstclear (&dirs, &a_split_clear);
	return (NULL);
}

void	get_aster_dir(char *path, t_list *dirs, t_list	**result)
{
	char			*cd;
	DIR				*dp;
	struct dirent	*ep;

	(void) result;
	if (!ft_strchr (dirs->content, '*'))
	{
		cd = sh_strcat (path, dirs->content);
		if (dirs->next)
			get_aster_dir (cd, dirs->next, result);
		else
			ft_lstadd_back (result, ft_lstnew (cd));
	}
	else
	{
		dp = opendir (path);
		if (dp == NULL)
			return (perror (path));
		ep = readdir (dp);
		while (ep)
		{
			if (ft_strcmp (ep->d_name, "..") && ft_strcmp (ep->d_name, ".")
				&& (wildcard_check (dirs->content, ep->d_name)))
			{
				cd = sh_strcat (path, ep->d_name);
				if (dirs->next)
				{
					if (ep->d_type == DT_DIR)
					{
						cd = sh_strcat_free (cd, "/", 1);
						get_aster_dir (cd, dirs->next, result);
					}
				}
				else
				{
					if (ep->d_type == DT_DIR || ep->d_type == DT_REG || ep->d_type == DT_LNK)
					{
						ft_lstadd_back (result, ft_lstnew (cd));
						printf ("%s\n", cd);
					}
				}
			}
			ep = readdir (dp);
		}
		(void) closedir (dp);
	}
}

int	wildcard_check(char *wildcard, char *str)
{
	t_list	*parts;
	char	*part[4];

	if (!ft_strcmp (wildcard, "*"))
		return (1);
	part[3] = ft_strdup (wildcard);
	if (part[3][ft_strlen (part[3]) - 1] == '/')
		part[3][ft_strlen (part[3]) - 1] = '\0';
	part[2] = str;
	parts = a_split (part[3], '*');
	while (parts)
	{
		part[0] = (char *)(parts->content);
		if (part[0][0] != '*')
		{
			part[1] = ft_strdup (part[0]);
			if (part[1][ft_strlen (part[1]) - 1] == '*')
				part[1][ft_strlen (part[1]) - 1] = '\0';
			part[2] = ft_strnstr (part[2], part[1], ft_strlen (part[2]));
			if (!part[2])
				return (free (part[1]), 0);
			part[2] += ft_strlen (part[1]);
			free (part[1]);
		}
		parts = parts->next;
	}
	if (ft_strlen (part[2]) > 0
		&& part[3][ft_strlen (part[3]) - 1] != '*')
		return (0);
	return (1);
}
