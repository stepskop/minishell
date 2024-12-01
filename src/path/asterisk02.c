/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:43:38 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/01 13:46:35 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*sh_remove_last_c(char *str, char c)
{
	char	*result;

	if (!str)
		return (NULL);
	result = ft_strdup (str);
	free (str);
	if (result[ft_strlen (result) - 1] == c)
		result[ft_strlen (result) - 1] = '\0';
	return (result);
}

t_de	*sh_new_de(unsigned char d_type, char *d_name, char *path[])
{
	t_de	*de;

	de = (t_de *) malloc (sizeof (t_de));
	if (!de)
		return (NULL);
	if (d_name)
		de->d_name = ft_strdup (d_name);
	else
		de->d_name = ft_strdup ("~");
	if ((!path[0] || path[0][ft_strlen (path[0]) - 1] == '/') || !d_name)
		de->rel_name = sh_strcat (path[0], d_name);
	else
		de->rel_name = sh_strcat_free (sh_strcat (path[0], "/"), d_name, 1);
	if (!path[1])
		de->full_name = ft_strdup (de->rel_name);
	else if ((path[1][ft_strlen (path[1]) - 1] == '/') || !d_name)
		de->full_name = sh_strcat (path[1], d_name);
	else
		de->full_name = sh_strcat_free (sh_strcat (path[1], "/"),
				d_name, 1);
	de->d_type = d_type;
	return (de);
}

void	dirs_clean(void *content)
{
	t_de	*de;

	de = (t_de *) content;
	free (de->d_name);
	free (de->full_name);
	free (de->rel_name);
	free (de);
}

int	dirs_check(char *d_name, char *pttrn, unsigned char d_type)
{
	if (!ft_strcmp (pttrn, "."))
		return (0);
	if (!ft_strcmp (d_name, ".."))
	{
		if (!ft_strcmp (pttrn, ".."))
			return (1);
		else
			return (0);
	}
	if (d_name[0] == '.' && pttrn[0] != '.')
		return (0);
	if (d_type != DT_DIR && d_type != DT_REG && d_type != DT_LNK)
		return (0);
	if (wildcard_check (pttrn, d_name))
		return (1);
	return (0);
}

void	dirs_init(t_list *dirs[], char *pathes[], t_list *dir)
{
	dirs[0] = NULL;
	dirs[1] = NULL;
	pathes[0] = ft_strdup (((t_de *)dir->content)->rel_name);
	pathes[1] = ft_strdup (((t_de *)dir->content)->full_name);
}

void	dirs_print(void *content)
{
	t_de	*de;

	de = (t_de *) content;
	printf ("(%u) %s\n\t%s\n\t%s\n", (unsigned int) de->d_type, de->d_name, de->rel_name, de->full_name); // remove
}

void	list_print(void *content)
{
	printf ("%s\n", (char *) content); // remove
}
