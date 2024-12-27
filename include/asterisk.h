/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:23:25 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/27 11:35:18 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTERISK_H
# define ASTERISK_H

# include "libft.h"

typedef struct s_dir_element
{
	unsigned char	d_type;
	char			*d_name;
	char			*full_name;
	char			*rel_name;
}	t_de;

// asterisk01.c
t_list		*get_dirs(char *pattern, char **envp);
int			get_lst_dirs(t_list **lst, char *pattern, char *path[]);
void		aster_recursion(t_list *dir, t_list *dirs, t_list **result);

// asterisk02.c
char		*sh_remove_last_c(char *str, char c);
t_de		*sh_new_de(unsigned char d_type, char *d_name, char *path[]);
void		dirs_clean(void *content);
int			dirs_check(char *d_name, char *pttrn);
void		dirs_init(t_list *dirs[], char *pathes[], t_list *dir);

// asterisk03.c
t_list		*aster_start(t_list *dirs);
void		aster_order(t_list *result);
int			aster_pathcmp(char *path1, char *path2);

// asterisk04.c
int			wildcard_check(char *wildcard, char *str);
char		*patern_prefix(char *patern, char *prefix, int first);
int			patern_suffix(const char *patern, const char *suffix);

#endif