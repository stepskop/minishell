/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:45:40 by username          #+#    #+#             */
/*   Updated: 2024/12/29 14:46:17 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_err(char *str)
{
	char	*msg;

	msg = ft_strjoin("sksh: ", str);
	if (!msg)
	{
		perror("malloc");
		return ;
	}
	ft_putstr_fd(msg, 2);
	free(msg);
}
