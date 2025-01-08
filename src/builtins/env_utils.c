/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:13:57 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/28 23:21:48 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	env_replace_var(char **envp, char *sv);

char	**envp_copy(char **envp1, char **envp2)
{
	char	**idx[2];

	idx[0] = envp1;
	idx[1] = envp2;
	while (*idx[0])
	{
		*idx[1] = *idx[0];
		idx[0]++;
		idx[1]++;
	}
	return (envp2);
}

int	envp_set_var(char ***envp, char *sv, int e_code)
{
	int		size;
	char	**new_envp;

	if (env_check_var (sv, e_code))
		return (1);
	if (env_replace_var (*envp, sv))
		return (0);
	size = sh_pstr_size (*envp);
	new_envp = (char **)malloc((size + 2) * sizeof (char *));
	if (!new_envp)
		return (perror("malloc"), 1);
	envp_copy (*envp, new_envp);
	new_envp[size] = ft_strdup (sv);
	new_envp[size + 1] = NULL;
	free(*envp);
	*envp = new_envp;
	return (0);
}

static int	env_replace_var(char **envp, char *sv)
{
	char	**envp_;
	char	*sv_;
	size_t	len;

	envp_ = envp;
	sv_ = get_env_name (sv);
	sv_ = sh_strjoin_free (sv_, "=", 1);
	len = sh_strlen (sv_);
	while (len && *envp_)
	{
		if (ft_strlen (*envp_) >= len && !ft_strncmp (*envp_, sv_, len))
		{
			free (*envp_);
			*envp_ = ft_strdup (sv);
			return (free (sv_), 1);
		}
		envp_++;
	}
	free (sv_);
	return (0);
}

// https://pubs.opengroup.org/onlinepubs/9699919799.2018edition/
// Env var's name: [a-zA-Z_]{1,}[a-zA-Z0-9_]*
int	env_check_var(char *var, int e_code)
{
	size_t	idx;

	if (!(ft_isalpha (var[0]) || var[0] == '_' || (var[0] == '?' && e_code)))
		return (sh_err ("not a valid identifier\n"), 1);
	idx = 1;
	while (var[idx] && var[idx] != '=')
	{
		if (!(ft_isalpha (var[idx]) || var[idx] == '_'
				|| ft_isdigit (var[idx])))
			return (sh_err ("not a valid identifier\n"), 1);
		idx++;
	}
	return (0);
}
