/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:34:17 by ksorokol          #+#    #+#             */
/*   Updated: 2024/11/20 17:15:29 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// The terminal process "/usr/bin/zsh" terminated with exit code: 2.

int	sh_execve(char *cmmnd)
{
	char	**smmnds;
	char	**args[3];
	int		rp;

	smmnds = sh_semicolon (cmmnd);
	while (*smmnds)
	{
		write (1, *smmnds, sh_strlen (*smmnds));
		write (1, "\n", 1);
		args[0] = sh_app_args (*smmnds);
		// args[1] = args[0] + 1;
		// rp = execve (args[0][0], &args[0][1], NULL); 
		// if (rp == -1)
		// 	write (1, "Something is wrong!\n", 20);
		// else
			// wait (&rp);
			waitpid (execve (args[0][0], &args[0][1], NULL), &rp, WNOHANG);
		smmnds++;
	}
	return (EXIT_SUCCESS);
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
