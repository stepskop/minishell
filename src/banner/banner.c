/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 00:13:19 by username          #+#    #+#             */
/*   Updated: 2024/12/30 00:15:04 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "banner.h"

void	print_banner(void)
{
	int		fd;
	char	*line;

	fd = open("banner.txt", O_RDONLY, 0600);
	if (fd == -1)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	printf("\n");
}
