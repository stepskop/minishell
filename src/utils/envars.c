/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envars.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 21:29:04 by username          #+#    #+#             */
/*   Updated: 2024/12/19 21:29:31 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*sh_getenv(char *name, char **envp)
{
	char	*str[3];
	char	**envp_;
	size_t	len;

	if (!name)
		return (NULL);
	str[0] = ft_strjoin (name, "=");
	if (!str[0])
		return (NULL);
	len = ft_strlen (str[0]);
	envp_ = envp;
	while (*envp_)
	{
		if (ft_strlen (*envp_) > len && !ft_strncmp (*envp_, str[0], len))
		{
			str[1] = ft_strchr (*envp_, '=');
			str[2] = ft_strdup (str[1] + 1);
			if (!str[2])
				perror("malloc");
			return (free (str[0]), str[2]);
		}
		envp_++;
	}
	return (free (str[0]), NULL);
}
