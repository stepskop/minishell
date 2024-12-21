/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:41:06 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/21 16:19:17 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	export(char **argv, char ***envp)
{
	char	**argv_;

	if (!argv || !envp)
		return (EXIT_SUCCESS);
	argv_ = argv + 1;
	while (*argv_)
	{
		if (!ft_strchr (*argv_, '='))
			*argv_ = sh_strjoin_free (*argv_, "=", 1);
		envp_set_var (envp, *argv_);
		argv_++;
	}
	return (EXIT_SUCCESS);
}
