/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:27:59 by ksorokol          #+#    #+#             */
/*   Updated: 2024/11/27 15:11:42 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_command(char **cmmnd);
// int		check_eol(char *str, t_counters_quotes	*cq);

int	main(int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	sig_init ();
	_loop_ (envp);
	rl_clear_history ();
	return (EXIT_SUCCESS);
}

void	_loop_(char **envp)
{
	char	*cmmnd[2];

	cmmnd[1] = put_env("abcde7$HOME 77$USER -$USERT");
	printf ("\nput_env(%s)->%s\n\n", "abcde7$HOME 77$USER -$USERT",  cmmnd[1]);
	free (cmmnd[1]);
	while (1)
	{
		cmmnd[1] = NULL;
		rl_on_new_line ();
		cmmnd[0] = get_command (&cmmnd[1]);
		add_history (cmmnd[1]);
		sh_run (cmmnd[1], envp);
		free (cmmnd[1]);
	}
}

char	*get_command(char **cmmnd)
{
	char	*line[2];
	int		i;

	line[1] = get_sh_pps ();
	while (1)
	{
		line[0] = readline(line[1]);
		i = sh_backslash (&line[0]);
		*cmmnd = sh_strjoin (*cmmnd, line[0]);
		if (!i)
		{
			if (sh_check_eol (*cmmnd))
			{
				if (line[1] && ft_strcmp (line[1], ">"))
					free (line[1]);
				return (*cmmnd);
			}
			*cmmnd = sh_strjoin (*cmmnd, ft_strdup ("\n"));
		}
		if (line[1] && ft_strcmp (line[1], ">"))
			free (line[1]);
		line[1] = ">";
	}
	return (*cmmnd);
}
