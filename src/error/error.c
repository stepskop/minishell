/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:45:40 by username          #+#    #+#             */
/*   Updated: 2024/11/27 18:50:18 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_err(char *str)
{
	char *msg;

	msg = ft_strjoin("sksh: ", str);
	if (!msg)
	{
		perror("malloc");
		return ;
	}
	ft_putstr_fd(msg, 2);
	free(msg);
}
