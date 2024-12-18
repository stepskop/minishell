/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:25:32 by username          #+#    #+#             */
/*   Updated: 2024/12/17 12:13:07 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline.h"

static void	read_stdin(int *pipefd, char *limiter)
{
	char	*line;
	char	*delimiter;

	delimiter = ft_strjoin(limiter, "\n");
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			free(delimiter);
			return ;
		}
		if (!ft_strcmp(line, delimiter))
		{
			free(delimiter);
			free(line);
			return ;
		}
		ft_putstr_fd(line, pipefd[1]);
		free(line);
	}
}

size_t	ex_cmdlen(t_args *args)
{
	size_t	len;
	t_args	*curr;

	len = 0;
	curr = args;
	while (curr)
	{
		if (curr->data)
		{
			len++;
			len += ft_strlen(curr->data);
		}
		curr = curr->next;
	}
	return (len);
}

int	ex_get_heredoc(t_args *args)
{
	int	pipefd[2];

	if (!args)
		return (sh_err("delimiter not specified\n"), -1);
	if (pipe(pipefd) == -1)
		return (perror("heredoc"), -1);
	read_stdin(pipefd, args->data);
	close(pipefd[1]);
	return (pipefd[0]);
}

int	ex_open_file(t_args *args, int oflag)
{
	int	fd;

	if (!args)
		return (sh_err("path not specified\n"), -1);
	fd = open(args->data, oflag, 0666);
	if (fd == -1)
		return (perror("open"), -1);
	return (fd);
}

int	ex_expand(t_args *args)
{
	t_args	*curr;
	char	*tmp;

	curr = args;
	while (curr)
	{
		if (curr->data)
		{
			tmp = curr->data;
			curr->data = put_env(curr->data);
			free(tmp);
			tmp = curr->data;
			curr->data = sh_asterisk(curr->data);
			free(tmp);
			if (!curr->data)
				return (0);
			curr = curr->next;
		}
	}
	return (1);
}
