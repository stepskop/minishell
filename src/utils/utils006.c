/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils006.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:27:59 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/27 13:08:25 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*sh_addspace(char **str, char *sym, int after)
{
	char	*str_;
	size_t	idx;

	if (!str || !sym)
		return (NULL);
	str_ = ft_strnstr(*str, sym, ft_strlen (*str));
	while (str_)
	{
		idx = str_ - *str;
		if (!sh_inquates (*str, idx))
		{
			if (after)
				idx += sh_addspace_a (str, idx, ft_strlen (sym));
			else
				idx += sh_addspace_b (str, idx);
		}
		str_ = ft_strnstr(&(*str)[idx + ft_strlen (sym)],
				sym, ft_strlen (*str));
	}
	return (*str);
}

char	sh_inquates(char *str, size_t idx)
{
	char	result;
	size_t	idx_;

	result = 0;
	idx_ = 0;
	while (idx_ < idx && str[idx_])
	{
		if (str[idx_] == '\'')
		{
			if (!result)
				result = str[idx_];
			else if (result == str[idx_])
				result = 0;
		}
		else if (str[idx_] == '"')
		{
			if (!result)
				result = str[idx_];
			else if (result == str[idx_])
				result = 0;
		}
		idx_++;
	}
	return (result);
}

size_t	sh_addspace_b(char **str, size_t idx)
{
	char	*str_;

	if (!idx || (*str)[idx - 1] == ' ' || (*str)[idx - 1] == (*str)[idx])
		return (0);
	str_ = ft_calloc (ft_strlen (*str) + 2, sizeof (char));
	if (!str_)
		return (perror("malloc"), 0);
	ft_memcpy (str_, *str, idx);
	str_[idx] = ' ';
	ft_memcpy (&str_[idx + 1], &(*str)[idx], ft_strlen (*str) - idx);
	str_[ft_strlen (*str) + 1] = '\0';
	free (*str);
	*str = str_;
	return (1);
}

size_t	sh_addspace_a(char **str, size_t idx, size_t len)
{
	char	*str_;

	if (!idx || (*str)[idx + len] == ' ' || (*str)[idx + len] == (*str)[idx])
		return (0);
	str_ = ft_calloc (ft_strlen (*str) + 2, sizeof (char));
	if (!str_)
		return (perror("malloc"), 0);
	ft_memcpy (str_, *str, idx + len);
	str_[idx + len] = ' ';
	ft_memcpy (&str_[idx + len + 1], &(*str)[idx + len],
		ft_strlen (*str) - (idx + len));
	str_[ft_strlen (*str) + 1] = '\0';
	free (*str);
	*str = str_;
	return (1);
}

char	*sh_addspace_all(char **str)
{
	sh_addspace (str, "<", 0);
	sh_addspace (str, "<", 1);
	sh_addspace (str, ">", 0);
	sh_addspace (str, ">", 1);
	sh_addspace (str, "|", 0);
	sh_addspace (str, "|", 1);
	return (*str);
}
