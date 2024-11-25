/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 23:53:25 by ksorokol          #+#    #+#             */
/*   Updated: 2024/11/25 15:20:42 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_builtins(char **argv)
{
	if (!ft_strcmp (argv[0], "exit"))
	{
		sh_ppfree (argv);
		exit (EXIT_SUCCESS);
	}
	else if (!ft_strcmp (argv[0], "echo")
		|| !ft_strncmp (argv[0], "echo ", 5))
		echo (argv);
	else if (!ft_strcmp (argv[0], "pwd")
		|| !ft_strncmp (argv[0], "pwd ", 4))
		pwd ();
	else if (!ft_strcmp (argv[0], "cd")
		|| !ft_strncmp (argv[0], "cd ", 3))
		cd (argv);
	return (0);
}
