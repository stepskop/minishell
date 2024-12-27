/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:11:51 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/27 11:29:31 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	dir_check(char *path);

int	cd(char **argv, char **envp)
{
	char	*path;

	if (argv[1] && argv[2])
	{
		sh_err ("cd: too many arguments\n");
		return (EXIT_FAILURE);
	}
	path = NULL;
	if (argv[1] && ft_strncmp (argv[1], "~", 1))
		path = ft_strdup (argv[1]);
	else
		path = cd_home (argv, envp);
	if (!dir_check (path))
		return (free (path), EXIT_FAILURE);
	else
		chdir (path);
	free (path);
	return (EXIT_SUCCESS);
}

char	*cd_home(char **argv, char **envp)
{
	char	*home;

	home = sh_getenv ("HOME", envp);
	if (!home)
		return (NULL);
	if (!argv[1])
		return (ft_strdup (home));
	else
		return (ft_strjoin (home, &argv[1][1]));
}

static int	dir_check(char *path)
{
	DIR		*dir;
	char	*str;

	dir = opendir (path);
	if (dir == NULL)
	{
		str = sh_strjoin ("cd: ", path);
		if (access (path, F_OK) == 0)
			str = sh_strjoin_free (str, ": Not a directory\n", 1);
		else
			str = sh_strjoin_free (str, ": No such file or directory\n", 1);
		sh_err (str);
		free (str);
		return (0);
	}
	closedir (dir);
	return (1);
}
