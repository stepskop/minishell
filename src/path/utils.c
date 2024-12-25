/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 21:22:45 by username          #+#    #+#             */
/*   Updated: 2024/12/23 16:41:52 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path.h"

static char	*cmd_from_path(char *cmd)
{
	char	*res;
	char	*path;
	char	**bin_dirs;
	char	*dir_slash;
	int		i;

	path = getenv("PATH");
	if (!path)
		return (NULL);
	bin_dirs = ft_split(path, ':');
	i = -1;
	while (bin_dirs[++i])
	{
		dir_slash = ft_strjoin(bin_dirs[i], "/");
		if (!dir_slash)
			return (sh_ppfree(bin_dirs), NULL);
		res = ft_strjoin(dir_slash, cmd);
		free(dir_slash);
		if (!res)
			return (sh_ppfree(bin_dirs), NULL);
		if (access(res, F_OK | X_OK) == 0)
			return (sh_ppfree(bin_dirs), res);
		free(res);
	}
	return (sh_ppfree(bin_dirs), NULL);
}

static char	*cmd_from_home(char *cmd)
{
	char	*home_dir;
	char	*res;

	home_dir = getenv("HOME");
	if (!home_dir)
		return (perror("PATH"), NULL);
	res = ft_strjoin(home_dir, cmd + 1);
	if (!res)
		return (perror("malloc"), NULL);
	return (res);
}

// static char	*cmd_from_curr(char *cmd)
// {
// 	char	curr_dir[PATH_MAX];
// 	char	*res;

// 	if (!getcwd(curr_dir, PATH_MAX))
// 		return (perror("getcwd"), NULL);
// 	res = ft_strjoin(curr_dir, cmd + 1);
// 	if (!res)
// 		return (perror("malloc"), NULL);
// 	return (res);
// }

static char	*cmd_from_root(char *cmd)
{
	char	*res;

	res = ft_strdup(cmd);
	if (!res)
		return (perror("malloc"), NULL);
	return (res);
}

char	*path_resolve(char *cmd)
{
	char	*res;

	if (!cmd || !*cmd)
		return (NULL);
	if (cmd[0] == '~')
		res = cmd_from_home(cmd);
	else if (cmd[0] == '.')
		res = cmd_from_root(cmd);
	else if (cmd[0] == '/')
		res = cmd_from_root(cmd);
	else
		res = cmd_from_path(cmd);
	if (!res)
		return (NULL);
	return (res);
}
