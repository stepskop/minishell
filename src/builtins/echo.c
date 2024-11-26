/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:11:55 by ksorokol          #+#    #+#             */
/*   Updated: 2024/11/26 18:50:26 by ksorokol         ###   ########.fr       */
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
	char	*env_name;
	size_t	len;
	char	*env_var;

	env_name = echo_get_env_name(dollar);
	len = 0;
	if (env_name)
	{
		len = ft_strlen (env_name);
		if (len > 0)
		{
			env_var = getenv(env_name);
			if (env_var)
				write (1, env_var, ft_strlen (env_var));
			else
				len = 0;
		}
	}
	if (len == 0)
		write (1, "$", 1);
	free (env_name);
	return (len);
}

char	*echo_get_env_name(char *dollar)
{
	size_t	idx;
	char	*env_name;

	idx = 1;
	if (!(ft_isalpha (dollar[idx]) || dollar[idx] == '_'))
		return (NULL);
	while (dollar[idx])
		if (!(ft_isdigit (dollar[idx]) || ft_isalpha (dollar[idx])
				|| dollar[idx] == '_'))
			break ;
	else
		idx++;
	env_name = (char *) malloc ((idx) * sizeof (char));
	if (!env_name)
		return (NULL);
	ft_memcpy (env_name, &dollar[1], idx - 1);
	env_name[idx - 1] = '\0';
	return (env_name);
}
