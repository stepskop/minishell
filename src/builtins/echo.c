/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:11:55 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/15 16:52:36 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	echo_write(char *arg);

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

static void	echo_write(char *arg)
{
	size_t	idx;

	idx = 0;
	while (arg[idx])
	{
		if (arg[idx] == '\\')
			idx++;
		write (1, &arg[idx], 1);
		idx++;
	}
}
