/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env02.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:13:57 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/05 19:13:03 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**envp_dup(char **envp)
{
	char	**new_envp;
	int		idx[2];

	new_envp = NULL;
	idx[0] = 0;
	idx[1] = envp_size (envp);
	if (idx[1] > 1)
	{
		new_envp = (char **) malloc ((idx[1] + 1) * sizeof (char *));
		if (!new_envp)
			return (NULL);
	}
	while (idx[0] < idx[1])
	{
		new_envp[idx[0]] = ft_strdup (envp[idx[0]]);
		idx[0]++;
	}
	new_envp[idx[0]] = NULL;
	return (new_envp);
}

char	**envp_copy(char **envp1, char **envp2)
{
	char	**idx[2];

	idx[0] = envp1;
	idx[1] = envp2;
	while (*idx)
	{
		*idx[1] = *idx[0];
		idx[0]++;
		idx[1]++;
	}
	return (envp2);
}

int	envp_size(char **envp)
{
	char	**idx;
	int		result;

	result = 0;
	idx = envp;
	while (*idx)
	{
		result++;
		idx++;
	}
	return (result);
}

char	*envp_set_var(char ***envp, char *sv)
{
	int		size;
	char	**new_envp;

	size = envp_size (*envp);
	new_envp = (char **) malloc ((size + 2) * sizeof (char *));
	if (!new_envp)
		return (sh_err ("envp_set_var - malloc error"), NULL);
	envp_copy (*envp, new_envp);
	new_envp[size] = ft_strdup (sv);
	new_envp[size + 1] = NULL;
	free(*envp);
	return (NULL);
}
