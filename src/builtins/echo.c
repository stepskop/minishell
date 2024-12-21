/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:11:55 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/21 16:08:59 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	echo_write(char *arg);
static int	echo_n_check(char *arg);

int	echo(char **argv)
{
	int		nnl;
	char	**arg;

	nnl = 0;
	arg = argv + 1;
	while (*arg)
	{
		if (echo_n_check (*arg))
			nnl = 1;
		else
			break ;
		arg++;
	}
	while (*arg)
	{
		echo_write (*arg);
		if (*(arg + 1))
			write (1, " ", 1);
		arg++;
	}
	if (!nnl)
		write (1, "\n", 1);
	return (EXIT_SUCCESS);
}

static void	echo_write(char *arg)
{
	write (1, arg, ft_strlen (arg));
}

static int	echo_n_check(char *arg)
{
	size_t	idx;

	if (arg[0] != '-')
		return (0);
	idx = 1;
	while (arg[idx])
	{
		if (arg[idx] != 'n')
			return (0);
		idx ++;
	}
	return (1);
}
