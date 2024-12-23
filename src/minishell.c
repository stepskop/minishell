/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:27:59 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/23 12:06:08 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "lexer.h"
#include "exec.h"
#include "signals.h"
#include "path.h"
#include "builtins.h"

static void	_loop_(char ***envp);
static char	*get_command(char **cmmnd, char *pps);
static void	ctrl_d(char *cmmnd, char **envp);
// int		check_eol(char *str, t_counters_quotes	*cq);

int	main(int argc, char **argv, char **envp)
{
	char	**envp_;

	envp_ = sh_pstrdup (envp);
	envp_set_var (&envp_, "?=0", 1);
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
	char		*tmp;

	while (1)
	{
		cmmnd[1] = NULL;
		rl_on_new_line ();
		cmmnd[0] = get_command (&cmmnd[1], get_sh_pps ());
		if (!cmmnd[0])
		{
			ctrl_d (cmmnd[1], *envp);
			continue ;
		}
		else if (!cmmnd[0][0])
			continue ;
		add_history (cmmnd[1]);
		tmp = put_env(cmmnd[0], *envp);
		splitted = sh_split_q(tmp, ' ');
		free(tmp);
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
		line = sh_strtrim (line, " ");
		if (!line[0] && !(*cmmnd))
			return (free (pps), free (line), "");
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
	{
		sh_err ("unexpected EOF while looking for matching \"\'\n");
		sh_err ("syntax error: unexpected end of file\n");
		free (cmmnd);
		return ;
	}
	else
		write (1, "exit\n", 5);
	sh_ppfree (envp);
	exit (EXIT_SUCCESS);
}
