/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:27:59 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/13 12:12:34 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_command(char **cmmnd);
// int		check_eol(char *str, t_counters_quotes	*cq);

int	main(int argc, char **argv, char **envp)
{
	// envp_set_get (envp, SET);
	((t_pv *)sh_get_pv ())->envp = envp_dup (envp);
	(void)argc;
	(void)argv;
	sig_init ();
	_loop_ (envp);
	rl_clear_history ();
	return (EXIT_SUCCESS);
}

t_pv	*sh_get_pv(void)
{
	static t_pv	pv = {NULL};

	return (&pv);
}

void	_loop_(char **envp)
{
	char		*cmmnd[2];
	t_prompt	*lst;
	char		**splitted;
	int			stdin_fd;
	int			exit_code;

	lst = NULL;
	while (1)
	{
		cmmnd[1] = NULL;
		rl_on_new_line ();
		cmmnd[0] = get_command (&cmmnd[1]);
		if (!cmmnd[0])
			continue ;
		add_history (cmmnd[1]);
		splitted = sh_split_q(cmmnd[0], ' ');
		if (splitted && splitted[0])
			lst = lexer(splitted);
		//if (lst)
		//	print_lex_dbg(lst);
		free (cmmnd[1]);
		stdin_fd = dup(STDIN_FILENO);
		executor(lst, envp);
		wait(&exit_code);
		lx_free_tokens(lst);
		dup2(stdin_fd, STDIN_FILENO);
		close(stdin_fd);
	}
}

char	*get_command(char **cmmnd)
{
	char	*line[2];
	int		i;

	line[1] = get_sh_pps ();
	while (1)
	{
		wait(NULL);
		line[0] = readline(line[1]);
		if (!line[0][0])
			return (NULL);
		i = sh_backslash (&line[0]);
		*cmmnd = sh_strjoin (*cmmnd, line[0]);
		free(line[0]);
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
