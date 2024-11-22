/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:24:25 by ksorokol          #+#    #+#             */
/*   Updated: 2024/11/22 16:24:04 by ksorokol         ###   ########.fr       */
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

char	*get_command(char *cmmnd)
{
	char	*str[2];
	char	**pathes[2];

	str[0] = getenv ("PATH");
	pathes[0] = ft_split (str[0], ':');
	pathes[1] = pathes[0];
	while (pathes[1])
	{
		
		pathes[1]++;
	}
	return (NULL);
}
