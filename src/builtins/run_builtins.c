/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 23:53:25 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/05 16:27:37 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_builtins(char **argv, char **envp, t_prompt *lst_node)
{
	t_prompt	*curr;

	if (!ft_strcmp (argv[0], "exit"))
	{
		curr = lst_node;
		while (curr && curr->prev)
			curr = curr->prev;
		lx_free_tokens(curr);
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
	else if (!ft_strcmp (argv[0], "env")
		|| !ft_strncmp (argv[0], "env ", 4))
		env (argv, envp);
	return (0);
}
