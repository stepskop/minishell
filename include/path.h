/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 21:23:15 by username          #+#    #+#             */
/*   Updated: 2024/12/27 11:41:50 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

# include "minishell.h"
# include "utils.h"

char		*path_resolve(char *cmd, char **envp);

// asterisk01.c
char		*sh_asterisk(char *astr, char **envp);

// a_split.c
t_list		*a_split(char *str, char c);
t_list		*a_split_elem(char *str, size_t idx[]);
void		a_split_clear(void *elem);

// path.c
char		*get_sh_path(int absolute_path, char **envp);
char		*get_sh_pps(char **envp);
// char		*get_cmd(char *cmd);
// char		*sh_replace_tilde(char *path, char **envp);
char		*sh_replace_dot(char *path, char **envp);
int			sh_checkcmd(char *cmmnd);

#endif
