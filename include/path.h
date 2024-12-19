/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 21:23:15 by username          #+#    #+#             */
/*   Updated: 2024/12/19 21:42:52 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

# include "minishell.h"
# include "utils.h"

char		*path_resolve(char *cmd);

// asterisk01.c
char		*sh_asterisk(char *astr);

// a_split.c
t_list		*a_split(char *str, char c);
t_list		*a_split_elem(char *str, size_t idx[]);
void		a_split_clear(void *elem);

// path.c
char		*get_sh_path(int absolute_path);
char		*get_sh_pps(void);
char		*get_cmd(char *cmd);
char		*sh_replace_tilde(char *path);
char		*sh_replace_dot(char *path);

#endif
