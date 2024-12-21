/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:52:22 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/21 16:10:56 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "path.h"

int	pwd(void)
{
	char	*str;

	str = get_sh_path (1);
	write (1, str, ft_strlen (str));
	write (1, "\n", 1);
	free (str);
	return (EXIT_SUCCESS);
}
