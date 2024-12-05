/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:43:38 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/05 11:51:06 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	sh_remove_last_c creates new string
*	and remove the last char if it equals c in new string
*/
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

/*
*	sh_new_de creates a new structure with name, full name and relative name of a dir
*/
t_de	*sh_new_de(unsigned char d_type, char *d_name, char *pathes[])
{
	t_de	*de;

	de = (t_de *) malloc (sizeof (t_de));
	if (!de)
		return (NULL);
	de->d_name = ft_strdup (d_name);
	if ((ft_strlen (pathes[0]) > 0
			&& pathes[0][ft_strlen (pathes[0]) - 1] == '/')
			|| !ft_strlen (pathes[0]))
		de->rel_name = sh_strjoin (pathes[0], d_name);
	else
		de->rel_name = sh_strjoin_free (sh_strjoin (pathes[0], "/"), d_name, 1);
	if ((ft_strlen (pathes[1]) > 0
			&& pathes[1][ft_strlen (pathes[1]) - 1] == '/')
			|| !ft_strlen (pathes[1]))
		de->full_name = sh_strjoin (pathes[1], d_name);
	else
		de->full_name = sh_strjoin_free
			(sh_strjoin (pathes[1], "/"), d_name, 1);
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

/*
*	dirs_check checks hiden dirs and need we it or not
*	then with check wildcard
*/
int	dirs_check(char *d_name, char *pttrn)
{
	if (d_name[0] == '.' && pttrn[0] != '.')
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

// void	dirs_print(void *content)	//	delete this functin 
// {
// 	t_de	*de;

// 	de = (t_de *) content;
// 	printf ("(%u) %s\n\t%s\n\t%s\n", (unsigned int) de->d_type,
// 		de->d_name, de->rel_name, de->full_name);
// }

// void	list_print(void *content)	//	delete this functin 
// {
// 	printf ("%s\n", (char *) content);
// }
