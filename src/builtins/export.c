/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:41:06 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/23 12:27:34 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	export(char **argv, char ***envp)
{
	char	**argv_;
	int		result[2];

	if (!argv || !envp)
		return (EXIT_FAILURE);
	result[0] = EXIT_SUCCESS;
	argv_ = argv + 1;
	while (*argv_)
	{
		if (!ft_strchr (*argv_, '='))
			*argv_ = sh_strjoin_free (*argv_, "=", 1);
		result[1] = envp_set_var (envp, *argv_, 0);
		if (result[1])
			result[0] = EXIT_FAILURE;
		argv_++;
	}
	return (result[0]);
}
