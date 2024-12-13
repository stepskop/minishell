/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env02.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:13:57 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/13 13:54:59 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

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

// int	envp_size(char **envp)
// {
// 	char	**idx;
// 	int		result;

// 	result = 0;
// 	idx = envp;
// 	while (*idx)
// 	{
// 		result++;
// 		idx++;
// 	}
// 	return (result);
// }

int	envp_set_var(char ***envp, char *sv)
{
	int		size;
	char	**new_envp;

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
