/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:24:25 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/23 16:59:27 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path.h"
#include <errno.h>

char	*get_sh_path(int absolute_path)
{
	char			*str[2];
	unsigned long	ul;

	str[0] = getenv ("HOME");
	ul = PATH_MAX;
	str[1] = (char *) malloc (ul * sizeof (char));
	if (!getcwd (str[1], ul))
		sh_err ("Something is wrong! (getcwd)");
	ul = ft_strlen (str[0]);
	if (absolute_path || ft_strncmp (str[0], str[1], ul))
	{
		str[0] = ft_strdup (str[1]);
		free (str[1]);
		return (str[0]);
	}
	if (ul > 1)
	{
		str[1][ul - 1] = '~';
		str[0] = ft_strdup (&str[1][ul - 1]);
	}
	free (str[1]);
	return (str[0]);
}

char	*get_sh_pps(void)
{
	char	*str[2];
	size_t	len;

	str[1] = sh_strjoin_free(CWD_COLOR, get_sh_path (0), 2);
	str[1] = sh_strjoin_free(str[1], RESET_COLOR, 1);
	len = ft_strlen (str[1]) + ft_strlen (PPS) + 3;
	str[0] = (char *) malloc (len * sizeof (char));
	if (!str[0])
		return (free (str[1]), NULL);
	str[0][0] = '\0';
	ft_strlcat (str[0], PPS, ft_strlen (str[0]) + ft_strlen (PPS) + 1);
	ft_strlcat (str[0], str[1], ft_strlen (str[0]) + ft_strlen (str[1]) + 1);
	free (str[1]);
	str[0][len - 3] = '$';
	str[0][len - 2] = ' ';
	str[0][len - 1] = '\0';
	return (str[0]);
}

char	*sh_replace_tilde(char *path)
{
	char	*result;

	if (path[0] == '~' && (path[1] == '/' || path[1] == '\0'))
	{
		result = ft_strdup (getenv ("HOME"));
		result = sh_strjoin_free (result, &path[1], 1);
		return (result);
	}
	return (ft_strdup (path));
}

char	*sh_replace_dot(char *path)
{
	char	*result;

	if (path[0] == '.' && (path[1] == '/' || path[1] == '\0'))
	{
		result = get_sh_path (1);
		result = sh_strjoin_free (result, &path[1], 1);
		return (result);
	}
	return (ft_strdup (path));
}

int	sh_checkcmd(char *cmmnd)
{
	DIR		*dir;
	char	*str;
	int		err_code;

	err_code = 126;
	dir = opendir (cmmnd);
	if (dir)
		str = sh_strjoin (cmmnd, ": Is a directory\n");
	else if (access (cmmnd, F_OK | X_OK) == -1)
	{
		if (errno == EACCES)
			str = sh_strjoin (cmmnd, ": Permission denied\n");
		else
		{
			str = sh_strjoin (cmmnd, ": No such file or directory\n");
			err_code = 127;
		}
	}
	else
		return (0);
	sh_err (str);
	free (str);
	closedir (dir);
	return (err_code);
}
