/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env01.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:41:06 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/11 11:05:54 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

void	env(char **argv, char **envp)
{
	char	**pstr;

	if (!argv[1])
	{
		env_print (envp);
		return ;
	}
	pstr = env_prsng (argv, envp);
	(void)pstr;
}

void	env_print(char **envp)
{
	char	**pstr;

	pstr = envp;
	while (*pstr)
	{
		write (1, *pstr, ft_strlen (*pstr));
		write (1, "\n", 1);
		pstr++;
	}
}

char	**env_prsng(char **argv, char **envp)
{
	char	**pstr[2];
	int		idx[3];
	char	*str;

	pstr[1] = envp_dup (envp);
	idx[0] = 1;
	idx[1] = envp_size (argv);
	while (idx[0] <= idx[1])
	{
		idx[2] = -1;
		if (argv[idx[0]] && ft_strchr (argv[idx[0]], '='))
			idx[2] = envp_set_var (&pstr[1], argv[idx[0]]);
		else if (idx[2] == -1)
		{
			str = sh_pstr2str (&argv[idx[0]], ' ');
			sh_run (str, pstr[1]);
			free (str);
			return (0);
		}
		(idx[0])++;
	}
	return (0);
}

int	env_check_var(char *var)
{
	(void)var;
	return (-1);
}

// env ete=set1 env ete2=set3 env
