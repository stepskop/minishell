/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:13:57 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/21 09:16:38 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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

int	envp_set_var(char ***envp, char *sv)
{
	int		size;
	char	**new_envp;

	if (!env_check_var (sv))
		return (0);
	size = sh_pstr_size (*envp);
	new_envp = (char **) malloc ((size + 2) * sizeof (char *));
	if (!new_envp)
		return (sh_err ("envp_set_var - malloc error"), 0);
	envp_copy (*envp, new_envp);
	new_envp[size] = ft_strdup (sv);
	new_envp[size + 1] = NULL;
	free(*envp);
	*envp = new_envp;
	return (1);
}

// https://pubs.opengroup.org/onlinepubs/7908799/xbd/envvar.html
int	env_check_var(char *var)
{
	if (!(ft_isalpha (var[0]) || var[0] == '_'))
		return (sh_err ("Environment variable's name should be [a-zA-Z_]{1,}[a-zA-Z0-9_]*\n"), 0);
	return (1);
}
