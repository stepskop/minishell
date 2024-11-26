/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:11:55 by ksorokol          #+#    #+#             */
/*   Updated: 2024/11/26 15:16:15 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char **argv)
{
	int		nnl;
	char	**arg;

	nnl = 0;
	if (argv[1] && !ft_strcmp (argv[1], "-n"))
		nnl = 1;
	arg = argv + 1 + nnl;
	while (*arg)
	{
		echo_write (*arg);
		if (*(arg + 1))
			write (1, " ", 1);
		arg++;
	}
	if (!nnl)
		write (1, "\n", 1);
}

void	echo_write(char *arg)
{
	int		q;
	size_t	idx[2];

	q = 0;
	idx[1] = ft_strlen (arg) - 1;
	idx[0] = 0;
	while (arg[idx[0]])
	{
		if (idx[0] == 0 && arg[idx[0]] == '"')
			q = 2;
		else if (idx[0] == 0 && arg[idx[0]] == '\'')
			q = 1;
		else
		{
			if (q != 1 && arg[idx[0]] == '$')
				idx[0] += echo_dollar (&arg[idx[0]]);
			else
				write (1, &arg[idx[0]], 1);
		}
		if (idx[0] == 0 && q)
			arg[ft_strlen (arg) - 1] = '\0';
		idx[0]++;
	}
}

size_t	echo_dollar(char *dollar)
{
	char	**split;
	size_t	len;
	char	*env_var;

	split = ft_split (dollar, ' ');
	len = 1;
	if (split && *split)
	{
		len = ft_strlen (*split);
		if (len > 1)
		{
			env_var = getenv(&(*split)[1]);
			if (env_var)
				write (1, env_var, ft_strlen (env_var));
			else
				len = 1;
		}
	}
	if (len == 1)
		write (1, "$", 1);
	sh_ppfree (split);
	return (len - 1);
}
