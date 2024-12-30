/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _malloc_.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 23:20:27 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/30 02:03:14 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_malloc_.h"
#include <unistd.h>

#define MEM_DEBUG

#ifdef MEM_DEBUG

void	*_malloc_(size_t __size)
{
	void	*mem;

	if (rand() % 10 < 2)
	{
		write (2, "_malloc_ returned NULL\n", 23);
		return (NULL);
	}
	mem = malloc (__size);
	if (!mem)
		perror("malloc");
	return (mem);
}
#endif

#ifndef MEM_DEBUG

void	*_malloc_(size_t __size)
{
	void	*mem;

	mem = malloc (__size);
	if (!mem)
		perror("malloc");
	return (mem);
}
#endif
