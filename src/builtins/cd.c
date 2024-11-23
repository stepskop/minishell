/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:11:51 by ksorokol          #+#    #+#             */
/*   Updated: 2024/11/23 17:28:05 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(char *arg)
{
	char	*str;

	if (!ft_strncmp (arg, "./", ft_strlen (arg))
		|| !ft_strncmp (arg, ".", ft_strlen (arg)))
		return ;
	str = get_sh_path (1);
}

char	*sh_check_path(char *path)
{
	char	*result;

	return (result);
}
