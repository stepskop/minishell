/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _malloc_.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 23:20:27 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/29 00:04:52 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_malloc_.h"
#include <unistd.h>

void	*_malloc_(size_t __size)
{
	if (rand() % 10 < 2)
	{
		write (2, "_malloc_ returned NULL\n", 23);
		return (NULL);
	}
	else
		return (malloc (__size));
}
