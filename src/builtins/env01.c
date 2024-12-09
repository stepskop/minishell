/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env01.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:41:06 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/09 13:24:34 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

void	env(char **argv, char **envp)
{
	char	**pstr;

	if (!argv[0])
	{
		env_print (envp);
		return ;
	}
	pstr = env_prsng (argv, envp);
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

	pstr[1] = envp_dup (envp);
	idx[0] = 1;
	idx[1] = envp_size (argv);
	while (idx[0] <	idx[1])
	{
		idx[2] = -1;
		if (ft_strchr (argv[idx[0]], '='))
			idx[2] = envp_set_var (&pstr[1], argv[idx[0]]);
		else if (idx[2] == -1)
			sh_run (argv[idx[0]], pstr[1]);
			// return (&argv[idx[0]]);
		idx[0]++;
	}
	return (0);
}

int	env_check_var(char *var)
{
	(void)var;
	return (-1);
}
