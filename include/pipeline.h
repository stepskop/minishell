/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:58:14 by username          #+#    #+#             */
/*   Updated: 2024/12/17 12:29:24 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H

# include "minishell.h"

int			ex_get_heredoc(t_args *args);
int			ex_open_file(t_args *args, int oflag);
size_t		ex_cmdlen(t_args *args);
int			ex_expand(t_args *args);
void		clean_pipes(t_prompt *node, int pipefd[2]);

#endif
