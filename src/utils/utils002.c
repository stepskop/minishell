/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils002.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:27:59 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/29 14:41:21 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*sh_strjoin(char *s1, char *s2)
{
	char	*result;
	size_t	len;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = 0;
	len_s2 = 0;
	if (s1)
		len_s1 = ft_strlen (s1);
	if (s2)
		len_s2 = ft_strlen (s2);
	len = len_s1 + len_s2 + 1;
	result = (char *)malloc(len * sizeof (char));
	if (!result)
		return (perror("malloc"), NULL);
	ft_memcpy (result, s1, len_s1);
	ft_memcpy (&result[len_s1], s2, len_s2);
	result[len - 1] = '\0';
	return (result);
}

char	*put_env(char *str, char **envp)
{
	char	*result;
	char	*buffer;
	size_t	idx[2];

	if (!str)
		return (NULL);
	if (str[0] == '\'' && str[ft_strlen (str) - 1] == '\'')
		return (ft_strdup (str));
	buffer = NULL;
	idx[0] = 0;
	idx[1] = 0;
	while (str[idx[1]])
	{
		if (str[idx[1]] == '$' && !sh_insq (str, idx[1]))
			buffer = str_join_env(str, buffer, idx, envp);
		idx[1]++;
	}
	result = sh_strjoin(buffer, &str[idx[0]]);
	free (buffer);
	if (!result)
		return (perror("malloc"), NULL);
	return (result);
}

char	*str_join_env(char *str, char *part1, size_t idx[], char **envp)
{
	char	*env_name;
	char	*env_var;
	size_t	len[2];
	char	*result;

	env_name = get_env_name (&str[idx[1] + 1]);
	if (!env_name)
	{
		env_var = ft_strdup ("$");
		env_name = ft_strdup ("");
	}
	else
		env_var = sh_getenv(env_name, envp);
	if (!env_var)
		env_var = ft_strdup ("");
	len[0] = sh_strlen (env_name);
	len[1] = 0;
	result = strs_cat (part1, str, env_var, idx);
	idx[1] += len[0];
	idx[0] = idx[1] + 1;
	free (part1);
	free (env_name);
	free (env_var);
	return (result);
}

char	*get_env_name(char *dollar)
{
	size_t	idx;
	char	*env_name;

	env_name = (char *) ft_calloc (2, sizeof (char));
	if (!env_name)
		return (perror("malloc"), NULL);
	if (ft_isdigit (dollar[0]) || dollar[0] == '?')
		return (env_name[0] = dollar[0], env_name);
	free (env_name);
	if (!(ft_isalpha (dollar[0]) || dollar[0] == '_'))
		return (NULL);
	idx = 1;
	while (dollar[idx] && (ft_isalpha (dollar[idx])
			|| ft_isdigit (dollar[idx]) || dollar[idx] == '_'))
		idx++;
	env_name = (char *)malloc((idx + 1) * sizeof (char));
	if (!env_name)
		return (perror("malloc"), NULL);
	ft_memcpy (env_name, dollar, idx);
	env_name[idx] = '\0';
	return (env_name);
}

char	*strs_cat(char *str_a, char *str_b, char *str_c, size_t idx_b[])
{
	char	*result;
	size_t	len[3];

	len[0] = 0;
	if (str_a)
		len[0] = ft_strlen(str_a);
	len[1] = idx_b[1] - idx_b[0];
	len[2] = ft_strlen(str_c);
	result = (char *)malloc((len[0] + len[1] + len[2] + 1) * sizeof (char));
	if (!result)
		return (perror("malloc"), NULL);
	ft_memcpy (result, str_a, len[0]);
	ft_memcpy (&result[len[0]], &str_b[idx_b[0]], len[1]);
	ft_memcpy (&result[len[0] + len[1]], str_c, len[2]);
	result[len[0] + len[1] + len[2]] = '\0';
	return (result);
}
