/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:11:51 by ksorokol          #+#    #+#             */
/*   Updated: 2024/11/28 19:06:04 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char **argv)
{
	DIR		*dir;
	char	*path;

	if (argv[1] && argv[2])
	{
		sh_err ("cd: too many arguments");
		return ;
	}
	path = NULL;
	if (!argv[1] || !ft_strncmp (argv[1], "~", 1))
		path = cd_home (argv);
	if (path)
	{
		free (argv[1]);
		argv[1] = path;
	}
	dir = opendir (argv[1]);
	if (dir == NULL)
		perror (argv[1]);
	else
		chdir (argv[1]);
	closedir (dir);
}

char	*cd_home(char **argv)
{
	char	*home;

	home = getenv ("HOME");
	if (!home)
		return (NULL);
	if (!argv[1])
		return (ft_strdup (home));
	else
		return (ft_strjoin (home, &argv[1][1]));
}
