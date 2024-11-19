/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:27:59 by ksorokol          #+#    #+#             */
/*   Updated: 2024/11/20 00:21:27 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_command(char **cmmnd);
int		check_eol(char *str, t_counters_quotes	*cq);

int	main(int argc, char *argv[])
{
	char	*cmmnd[2];

	if (argc > 1)
		argv[0] = argv[0];
	while (1)
	{
		cmmnd[1] = NULL;
		cmmnd[0] = get_command (&cmmnd[1]);
		write (1, cmmnd[1], sh_strlen (cmmnd[1]));
		// write (1, "\n", 1);
		if (!ft_strcmp (cmmnd[0], "exit"))
		{
			free (cmmnd[1]);
			// free (cmmnd[0]);
			break ;
		}
		free (cmmnd[1]);
		// free (cmmnd[0]);
	}
	return (EXIT_SUCCESS);
}

char	*get_command(char **cmmnd)
{
	char	*line[2];
	int		i;

	line[1] = PPS;
	while (1)
	{
		line[0] = readline(line[1]);
		i = sh_backslash (&line[0]);
		*cmmnd = sh_strjoin (*cmmnd, line[0]);
		if (!i)
		{
			if (sh_check_eol (*cmmnd))
				return (*cmmnd);
			*cmmnd = sh_strjoin (*cmmnd, ft_strdup ("\n"));
		}
		line[1] = ">";
	}
	return (*cmmnd);
}
