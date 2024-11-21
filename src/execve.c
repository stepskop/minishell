/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:34:17 by ksorokol          #+#    #+#             */
/*   Updated: 2024/11/21 00:29:46 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sh_execve(char *cmmnd)
{
	char	**cmmnds_args[3];
	int		rp;
	pid_t	pid;

	cmmnds_args[0] = sh_semicolon (cmmnd);
	cmmnds_args[1] = cmmnds_args[0];
	while (*cmmnds_args[1])
	{
		cmmnds_args[2] = sh_app_args (*cmmnds_args[1]);
		pid = fork ();
		if (pid == 0)
		{
			rl_clear_history ();
			free (cmmnd);
			sh_ppfree (cmmnds_args[0]);
			if (execve (cmmnds_args[2][0], cmmnds_args[2], NULL) == -1)
				write (1, "Something is wrong!\n", 20);
			sh_ppfree (cmmnds_args[2]);
			exit (EXIT_SUCCESS);
		}
		sh_ppfree (cmmnds_args[2]);
		waitpid (pid, &rp, 0);
		cmmnds_args[1]++;
	}
	return (sh_ppfree (cmmnds_args[0]), EXIT_SUCCESS);
}

char	**sh_semicolon(char *cmmnd)
{
	return (ft_split (cmmnd, ';'));
}

char	**sh_app_args(char *cmmnd)
{
	return (ft_split (cmmnd, ' '));
}

// char	*get_path(char	*app)
// {
// 	char *env_path;
// 	char **pathes;

// 	env_path = getenv("PATH");
// 	pathes = ft_split (env_path, ':');
// 	// while 
// 	return (NULL);
// }
