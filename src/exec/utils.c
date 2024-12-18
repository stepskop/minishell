/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:49:36 by username          #+#    #+#             */
/*   Updated: 2024/11/26 15:50:00 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <linux/limits.h>
#include <time.h>

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

static char	*cmd_from_curr(char *cmd)
{
	char	curr_dir[PATH_MAX];
	char	*res;

	if (!getcwd(curr_dir, PATH_MAX))
		return (perror("getcwd"), NULL);
	res = ft_strjoin(curr_dir, cmd + 1);
	if (!res)
		return (perror("malloc"), NULL);
	return (res);
}

char	*get_cmd(char *cmd)
{
	char	*res;

	if (!cmd || !*cmd)
		return (NULL);
	if (cmd[0] == '~')
		res = cmd_from_home(cmd);
	else if (cmd[0] == '.')
		res = cmd_from_curr(cmd);
	else
		res = cmd_from_path(cmd);
	return (res);
}

void	sh_subprocess_pipes(int pipefd[2])
{
	if (pipefd[0] > 0)
		dup2(pipefd[0], STDIN_FILENO);
	if (pipefd[1] > 1)
		dup2(pipefd[1], STDOUT_FILENO);
	if (pipefd[1] > 1)
		close(pipefd[1]);
	if (pipefd[0] > 0)
		close(pipefd[0]);
}
