/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 12:32:01 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/21 15:29:02 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	**unset_var(char ***envp, char *uv);

void	unset(char **argv, char ***envp)
{
	char	**argv_;
	char	**argv_new;
	char	*uv_;

	argv_ = argv + 1;
	while (*argv_)
	{
		uv_ = sh_getenv (*argv_, *envp);
		if (!uv_)
		{
			argv_++;
			continue ;
		}
		free (uv_);
		argv_new = unset_var (envp, *argv_);
		if (argv_new)
		{
			sh_ppfree (*envp);
			*envp = argv_new;
		}
		argv_++;
	}
}

static char	**unset_var(char ***envp, char *uv)
{
	char	**envp_[3];
	char	*uv_;
	size_t	len;

	uv_ = ft_strjoin(uv, "=");
	envp_[0] = *envp;
	len = sh_strlen (uv_);
	envp_[1] = (char **) malloc ((sh_pstr_size (*envp)) * sizeof (char *));
	if (!envp_[1])
		return (sh_err ("unset_var - malloc error"), NULL);
	envp_[2] = envp_[1];
	while (*envp_[0])
	{
		if (ft_strlen (*envp_[0]) > len && ft_strncmp (*envp_[0], uv_, len))
		{
			*envp_[2] = ft_strdup (*envp_[0]);
			envp_[2]++;
		}
		envp_[0]++;
	}
	*envp_[2] = NULL;
	return (free (uv_), envp_[1]);
}
