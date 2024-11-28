/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:43:38 by ksorokol          #+#    #+#             */
/*   Updated: 2024/11/28 19:08:16 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*sh_asterisk (char *astr)
{
	char	**dirs;
	t_list	*result;
	char	*sd;

	if (!astr)
		return (NULL);
	if ((astr[0] == '\'' && astr[ft_strlen (astr) - 1] == '\'')
		|| (astr[0] == '"' && astr[ft_strlen (astr) - 1] == '"')
		|| !ft_strchr (astr, '*'))
		return (ft_lstnew (ft_strdup (astr)));
	dirs = ft_split (astr, '/');
	
	return (NULL);
}

char	*get_start_dir (char *path)
{
	char	*sd;

	if (path[0] == '.' && path[1] =='\0')
	{
		sd = (char *) malloc (PATH_MAX * sizeof (char));
		if (!sd)
			return (NULL);
		if (!getcwd (sd, PATH_MAX))
		{
			sh_err ("Something is wrong! (getcwd)");
			return (free (path), NULL);
		}
	}
	else if (path[0] == '~' && path[1] =='\0')
}

t_list	*sh_aster_dir (char *sd, t_list *result, char **dirs)
{
	DIR		*dp;
	struct dirent *ep;

	dp = opendir (sd);
	if (dp == NULL)
		perror (sd);
}
