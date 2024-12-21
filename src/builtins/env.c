/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:41:06 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/21 16:17:55 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "lexer.h"
#include "exec.h"

/*
*	original envp in the parent process
*	not freeing in env recursion process
*	now keep it without freeing ( see the subject :) )
*	this is not a leak, it's still reachable ...
*/
int	env(char **argv, char **envp)
{
	int	result;

	if (!argv[1])
	{
		env_print (envp);
		return (sh_ppfree (envp), EXIT_SUCCESS);
	}
	result = env_prsng (argv, &envp);
	return (result);
}

void	env_print(char **envp)
{
	char	**pstr;

	if (!envp)
		return ;
	pstr = envp;
	while (*pstr)
	{
		write (1, *pstr, ft_strlen (*pstr));
		write (1, "\n", 1);
		pstr++;
	}
}

int	env_prsng(char **argv, char ***penvp)
{
	char		**pstr[2];
	int			idx[4];
	t_prompt	*lst;

	idx[0] = 0;
	idx[1] = sh_pstr_size (argv);
	while (++idx[0] < idx[1])
	{
		idx[2] = -1;
		if (argv[idx[0]] && ft_strchr (argv[idx[0]], '='))
			idx[2] = envp_set_var (penvp, argv[idx[0]], 0);
		else if (idx[2] == -1)
		{
			lst = lexer (sh_pstrdup (&argv[idx[0]]));
			executor (lst, penvp);
			wait (&idx[3]);
			free_prompt(lst);
			return (sh_ppfree (*penvp), idx[3]);
		}
		if (!idx[2])
			return (sh_ppfree (*penvp), EXIT_SUCCESS);
	}
	pstr[1] = sh_split_q ("env", ' ');
	idx[3] = env (pstr[1], *penvp);
	return (sh_ppfree (pstr[1]), idx[3]);
}
