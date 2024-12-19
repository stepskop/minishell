/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:27:59 by ksorokol          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/12/21 15:43:19 by ksorokol         ###   ########.fr       */
=======
/*   Updated: 2024/12/19 22:48:35 by username         ###   ########.fr       */
>>>>>>> b2887ec (chore: exit builtins correctly, try to capture exit code)
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "lexer.h"
#include "exec.h"
#include "signals.h"
#include "path.h"

static void	_loop_(char ***envp);
static char	*get_command(char **cmmnd, char *pps);
static void	ctrl_d(char *cmmnd, char **envp);
// int		check_eol(char *str, t_counters_quotes	*cq);

int	main(int argc, char **argv, char **envp)
{
	char	**envp_;

	envp_ = sh_pstrdup (envp);
	if (!envp_)
		return (perror("malloc"), EXIT_FAILURE);
	(void)argc;
	(void)argv;
	sig_init ();
	_loop_ (&envp_);
	sh_ppfree (envp_);
	rl_clear_history ();
	return (EXIT_SUCCESS);
}

static void	_loop_(char ***envp)
{
	char		*cmmnd[2];
	t_prompt	*lst;
	char		**splitted;

	while (1)
	{
		cmmnd[1] = NULL;
		rl_on_new_line ();
		cmmnd[0] = get_command (&cmmnd[1], get_sh_pps ());
		if (!cmmnd[0])
			ctrl_d (cmmnd[1], *envp);
		else if (!cmmnd[0][0])
			continue ;
		add_history (cmmnd[1]);
		splitted = sh_split_q(cmmnd[0], ' ');
		if (splitted && splitted[0])
			lst = lexer(splitted);
		free (cmmnd[1]);
		executor(lst, envp);
		free_prompt(lst);
	}
}

static char	*get_command(char **cmmnd, char *pps)
{
	char	*line;
	int		i;

	while (1)
	{
		wait(NULL);
		line = readline(pps);
		if (!line)
			return (free (pps), NULL);
		if (!line[0] && !(*cmmnd))
			return (free (pps), line);
		i = sh_backslash (&line);
		*cmmnd = sh_strjoin_free(*cmmnd, line, 3);
		if (!i)
		{
			if (sh_check_eol (*cmmnd))
				return (free (pps), *cmmnd);
			*cmmnd = sh_strjoin_free (*cmmnd, ft_strdup ("\n"), 3);
		}
		free (pps);
		pps = ft_strdup (">");
	}
	return (free (pps), *cmmnd);
}

static void	ctrl_d(char *cmmnd, char **envp)
{
	if (cmmnd)
		free (cmmnd);
	else
		write (1, "exit\n", 5);
	sh_ppfree (envp);
	exit (EXIT_SUCCESS);
}
