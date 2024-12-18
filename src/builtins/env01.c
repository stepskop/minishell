/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env01.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:41:06 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/13 14:32:59 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

char	*sh_getenv(char *name)
{
	char	*str[3];
	char	**envp_;
	size_t	len;

	if (!name)
		return (NULL);
	str[0] = ft_strjoin (name, "=");
	len = ft_strlen (str[0]);
	envp_ = sh_get_pv()->envp;
	while (*envp_)
	{
		if (ft_strlen (*envp_) > len && !ft_strncmp (*envp_, str[0], len))
		{
			str[1] = ft_strchr (*envp_, '=');
			str[2] = ft_strdup (str[1] + 1);
			return (free (str[0]), str[2]);
		}
		envp_++;
	}
	return (NULL);
}

void	env(char **argv, char **envp)
{
	char	**pstr;

	if (!argv[1])
	{
		env_print (envp);
		return ;
	}
	pstr = env_prsng (argv, envp);
	(void)pstr;
}

void	env_print(char **envp)
{
	char	**pstr;

	pstr = envp;
	while (*pstr)
	{
		write (1, *pstr, ft_strlen (*pstr));
		write (1, "\n", 1);
		pstr++;
	}
}

char	**env_prsng(char **argv, char **envp)
{
	char		**pstr[2];
	int			idx[4];
	t_prompt	*lst;

	pstr[0] = sh_pstrdup (envp);
	idx[0] = 1;
	idx[1] = sh_pstr_size (argv);
	while (idx[0] < idx[1])
	{
		idx[2] = -1;
		if (argv[idx[0]] && ft_strchr (argv[idx[0]], '='))
			idx[2] = envp_set_var (&pstr[0], argv[idx[0]]);
		else if (idx[2] == -1)
		{
			lst = lexer (sh_pstrdup (&argv[idx[0]]));
			executor (lst, pstr[0]);
			wait (&idx[3]);
			lx_free_tokens(lst);
			return (sh_ppfree(pstr[0]), NULL);
		}
		(idx[0])++;
	}
	pstr[1] = sh_split_q ("env", ' ');
	env (pstr[1], pstr[0]);
	return (sh_ppfree (pstr[0]), sh_ppfree (pstr[1]), NULL);
}

int	env_check_var(char *var)
{
	(void)var;
	return (-1);
}

// env ete=set1 env ete2=set3 env
