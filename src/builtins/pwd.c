/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:52:22 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/27 11:32:51 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "path.h"

int	pwd(char **envp)
{
	char	*str;

	str = get_sh_path (1, envp);
	write (1, str, ft_strlen (str));
	write (1, "\n", 1);
	free (str);
	return (EXIT_SUCCESS);
}
