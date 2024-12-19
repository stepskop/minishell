/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils003.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:27:59 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/19 21:35:45 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*sh_strjoin_free(char *s1, char *s2, int opt)
{
	char	*result;

	result = sh_strjoin (s1, s2);
	if (opt == 1)
		free (s1);
	else if (opt == 2)
		free (s2);
	else if (opt == 3)
	{
		free (s1);
		free (s2);
	}
	return (result);
}

void	sh_del_arr(void *arr[], int arr_size)
{
	int	idx;

	idx = 0;
	while (idx < arr_size)
	{
		free (arr[idx]);
		idx++;
	}
}

char	*sh_lst2str(t_list *lst, char c)
{
	char	*result;
	t_list	*l;
	char	*str;

	result = NULL;
	l = lst;
	while (l)
	{
		result = sh_strjoin_free (result, l->content, 1);
		if (l->next)
		{
			str = (char *) malloc(2 * sizeof (char));
			str[0] = c;
			str[1] = '\0';
			result = sh_strjoin_free (result, str, 3);
		}
		l = l->next;
	}
	return (result);
}

char	*sh_pstr2str(char **pstr, char c)
{
	char	*result;
	char	**pp;
	char	*str;

	result = NULL;
	pp = pstr;
	while (*pp)
	{
		result = sh_strjoin_free (result, *pp, 1);
		if (c && *(pp + 1))
		{
			str = (char *) malloc(2 * sizeof (char));
			str[0] = c;
			str[1] = '\0';
			result = sh_strjoin_free (result, str, 3);
		}
		pp++;
	}
	return (result);
}

char	**sh_pstrdup(char **pstr)
{
	char	**new_envp;
	int		idx[2];

	if (!pstr)
		return (NULL);
	new_envp = NULL;
	idx[0] = 0;
	idx[1] = sh_pstr_size (pstr);
	if (idx[1] > 0)
	{
		new_envp = (char **) malloc ((idx[1] + 1) * sizeof (char *));
		if (!new_envp)
			return (NULL);
	}
	while (idx[0] < idx[1])
	{
		new_envp[idx[0]] = ft_strdup (pstr[idx[0]]);
		idx[0]++;
	}
	new_envp[idx[0]] = NULL;
	return (new_envp);
}
