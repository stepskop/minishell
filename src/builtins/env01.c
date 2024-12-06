/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env01.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:41:06 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/06 13:48:34 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(char **argv, char **envp)
{
	char	**pstr[2];

	pstr[1] = envp;
	if (!argv[1] || (!ft_strcmp ("env", argv[1]) && !argv[2]))
	{
		while (*pstr[1])
		{
			write (1, *pstr[1], ft_strlen (*pstr[1]));
			write (1, "\n", 1);
			pstr[1]++;
		}
		return ;
	}
	env_prsng (argv, envp);
}

int	env_prsng(char **argv, char **envp)
{
	char	**pstr[2];
	int		idx[3];

	pstr[1] = envp_dup (envp);
	idx[0] = 1;
	idx[1] = envp_size (argv);
	while (idx[0] <	idx[1])
	{
		idx[2] = -1;
		pstr[0] = sh_split_q (argv[idx[0]], '=');
		if (pstr[0][0] && pstr[0][1])
			idx[2] = env_check_var (pstr[0]);		
		if (idx[2] == -1)
		{
			if (env_check_var(pstr[1]) >= 0)
				;
				// sh_run ();
			sh_ppfree (pstr[1]);
		}
		sh_ppfree (pstr[0]);
		idx[0]++;
	}
	return (0);
}

int	env_check_var(char **var)
{
	(void)var;
	return (-1);
}
