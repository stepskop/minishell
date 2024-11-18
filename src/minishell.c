/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:27:59 by ksorokol          #+#    #+#             */
/*   Updated: 2024/11/18 17:15:18 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_command(char *cmmnd);

int	main(int argc, char *argv[])
{
	char	*cmmnd[2];

	if (argc > 1)
		argv[0] = argv[0];
	while (1)
	{
		cmmnd[0] = get_command (cmmnd[1]);
	}
	return (EXIT_SUCCESS);
}

char	*get_command(char *cmmnd)
{
	char	*buffer;

	buffer = readline(PPS);
	while (buffer[ft_strlen(buffer)] == '\\')
	{
		buffer = readline(">");
	}
	add_history(buffer);
	cmmnd = buffer;
	return (buffer);
}
