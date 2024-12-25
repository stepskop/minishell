/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 21:16:25 by username          #+#    #+#             */
/*   Updated: 2024/12/24 02:27:04 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

// utils001.c
size_t		sh_strlen(const char *s);
int			sh_check_eol(char *cmmnd);
int			sh_backslash(char **line);
// char	*sh_strjoin(char *s1, char *s2);
void		sh_ppfree(char	**pp);
char		*sh_strdup(char *str);

// quotation.c
int			check_quot(char *str);
char		*del_quot(char *str);

// utils002.c
char		*sh_strjoin(char *s1, char *s2);
char		*put_env(char *str, char **envp);
char		*str_join_env(char *str, char *part1, size_t idx[], char **envp);
char		*get_env_name(char *dollar);
char		*strs_cat(char *str_a, char *str_b, char *str_c, size_t idx_b[]);

// utils003.c
char		*sh_strjoin_free(char *s1, char *s2, int opt);
void		sh_del_arr(void *arr[], int arr_size);
char		*sh_lst2str(t_list *lst, char c);
char		*sh_pstr2str(char **pstr, char c);
char		**sh_pstrdup(char **pstr);

// utils004.c
int			sh_pstr_size(char **pstr);
char		*sh_unquotes(char *arg);
char		sh_bsq(char *arg, size_t idx);
char		**sh_uq_args(char **args);
char		*sh_strtrim(char *s1, char *set);

// utils005.c
char		*sh_rmbs(char *arg);
char		**sh_rmbs_args(char **args);
char		**sh_ud_rmbs(char **args);
int			sh_insq(char *arg, size_t pos);
size_t		sh_setchstr(char *str_d, size_t idx_d, char *str_s, size_t idx_s);

// sh_split_q.c
char		**sh_split_q(char *str, char c);

// Environ
char		*sh_getenv(char *name, char **envp);

// Err
void		sh_err(char *str);

// Memory
void		free_args(t_args *args);
void		free_prompt(t_prompt *lst);
void		free_ast(t_ast *ast);
void		free_ast_node(t_ast *node);

#endif
