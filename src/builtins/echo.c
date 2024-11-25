/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:11:55 by ksorokol          #+#    #+#             */
/*   Updated: 2024/11/25 15:24:55 by ksorokol         ###   ########.fr       */
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
		write (1, *arg, ft_strlen (*arg));
		if (*(arg + 1))
			write (1, " ", 1);
		arg++;
	}
	if (!nnl)
		write (1, "\n", 1);
}
