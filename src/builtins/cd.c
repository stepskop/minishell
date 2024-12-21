/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:11:51 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/20 16:24:38 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	cd(char **argv)
{
	DIR		*dir;
	char	*path;

	if (argv[1] && argv[2])
	{
		sh_err ("cd: too many arguments\n");
		return ;
	}
	path = NULL;
	if (argv[1] && ft_strncmp (argv[1], "~", 1))
		path = ft_strdup (argv[1]);
	else
		path = cd_home (argv);
	dir = opendir (path);
	if (dir == NULL)
		perror (path);
	else
		chdir (path);
	closedir (dir);
	free (path);
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
