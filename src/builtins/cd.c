/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:11:51 by ksorokol          #+#    #+#             */
/*   Updated: 2024/11/25 02:38:30 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char **argv)
{
	DIR		*dir;
	char	*home;

	if (argv[1] && argv[2])
	{
		write (1, "cd: too many arguments\n", 23);
		return ;
	}
	home = getenv ("HOME");
	if (!argv[1] || !ft_strncmp (argv[1], "~", ft_strlen (argv[1])))
	{
		chdir (home);
		return ;
	}
	if (!ft_strncmp (argv[1], "./", ft_strlen (argv[1]))
		|| !ft_strncmp (argv[1], ".", ft_strlen (argv[1])))
		return ;
	dir = opendir (argv[1]);
	if (dir == NULL)
		perror (argv[1]);
	else
		chdir (argv[1]);
	free (dir);
}
