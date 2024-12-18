/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:39:55 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/13 14:20:29 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

// env01.c
void	env_print(char **envp);
char	**env_prsng(char **argv, char **envp);
int		env_check_var(char *var);

// env02.c
char	**envp_copy(char **envp1, char **envp2);
int		envp_set_var(char ***envp, char *sv);

#endif
