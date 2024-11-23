/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:27:59 by ksorokol          #+#    #+#             */
/*   Updated: 2024/11/23 14:28:40 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_command(char **cmmnd);
// int		check_eol(char *str, t_counters_quotes	*cq);

int	main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	sig_init ();
	// kill (getpid(), SIGTERM);
	_loop_ ();
	rl_clear_history ();
	return (EXIT_SUCCESS);
}

void	_loop_(void)
{
	char	*cmmnd[2];

	while (1)
	{
		cmmnd[1] = NULL;
		rl_on_new_line ();
		cmmnd[0] = get_command (&cmmnd[1]);
		add_history (cmmnd[1]);
		if (!ft_strcmp (cmmnd[0], "exit"))
		{
			free (cmmnd[1]);
			// free (cmmnd[0]);
			break ;
		}
		else if (!ft_strcmp (cmmnd[0], "pwd"))
			pwd ();
		else
			sh_run (cmmnd[1]);
		free (cmmnd[1]);
		// free (cmmnd[0]);
	}
}

char	*get_command(char **cmmnd)
{
	char	*line[2];
	int		i;

	line[1] = NULL;
	while (1)
	{
		if (line[1])
			free (line[1]);
		line[1] = get_sh_pps ();
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
