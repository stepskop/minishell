/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:24:25 by ksorokol          #+#    #+#             */
/*   Updated: 2024/11/23 14:55:36 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_sh_path(int absolute_path)
{
	char			*str[2];
	unsigned long	ul;

	str[0] = getenv ("HOME");
	ul = PATH_MAX;
	str[1] = (char *) malloc (ul * sizeof (char));
	if (!getcwd (str[1], ul))
		write (1, "Something is wrong! (getcwd)\n", 29);
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

	str[1] = get_sh_path (0);
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

char	*get_ext_command(char *cmmnd)
{
	char	*result;
	char	**pathes[2];

	if (access(cmmnd, F_OK) == 0)
		return (ft_strdup (cmmnd));
	result = getenv ("PATH");
	pathes[0] = ft_split (result, ':');
	pathes[1] = pathes[0];
	while (*pathes[1])
	{
		if ((*pathes[1])[ft_strlen (*pathes[1]) - 2] != '/')
			*pathes[1] = sh_strcat(*pathes[1], "/");
		result = sh_strcat(*pathes[1], cmmnd);
		if (access(result, F_OK) == 0)
			return (sh_ppfree (pathes[0]), result);
		free (result);
		pathes[1]++;
	}
	sh_ppfree (pathes[0]);
	return (NULL);
}
