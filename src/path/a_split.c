/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_split.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:43:38 by ksorokol          #+#    #+#             */
/*   Updated: 2024/11/28 23:42:05 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*a_split(char *str, char c)
{
	t_list	*llist[2];
	size_t	idx[2];

	llist[0] = NULL;
	idx[0] = 0;
	idx[1] = -1;
	while (str[++idx[1]])
	{
		if (str[idx[1]] == c)
		{
			llist[1] = a_split_elem (str, idx);
			if (!llist[1])
				return (ft_lstclear (&llist[0], &a_split_clear), NULL);
			ft_lstadd_back (&llist[0], llist[1]);
			idx[0] = idx[1] + 1;
		}
	}
	if (idx[0] != idx[1])
	{
		llist[1] = a_split_elem (str, idx);
		if (!llist[1])
			return (ft_lstclear (&llist[0], &a_split_clear), NULL);
		ft_lstadd_back (&llist[0], llist[1]);
	}
	return (llist[0]);
}

t_list	*a_split_elem(char *str, size_t idx[])
{
	char	*elem;

	elem = (char *) malloc ((idx[1] - idx[0] + 2) * sizeof (char));
	if (!elem)
		return (NULL);
	ft_memcpy (elem, &str[idx[0]], idx[1] - idx[0] + 1);
	elem[idx[1] - idx[0] + 1] = '\0';
	return (ft_lstnew (elem));
}

void	a_split_clear(void *elem)
{
	free (elem);
}
