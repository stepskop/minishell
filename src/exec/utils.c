/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:25:32 by username          #+#    #+#             */
/*   Updated: 2024/12/26 15:21:15 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "path.h"

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
	char	*filename;

	if (!args)
		return (sh_err("delimiter not specified\n"), -1);
	if (pipe(pipefd) == -1)
		return (perror("heredoc"), -1);
	filename = sh_unquotes (args->data);
	read_stdin(pipefd, args->data);
	free (filename);
	close(pipefd[1]);
	return (pipefd[0]);
}

int	ex_open_file(t_args *args, int oflag)
{
	int		fd;
	char	*filename;

	if (!args)
		return (sh_err("path not specified\n"), -1);
	filename = sh_unquotes (args->data);
	fd = open(filename, oflag, 0666);
	free (filename);
	if (fd == -1)
		return (perror("open"), -1);
	return (fd);
}

int	ex_expand(t_args *args, char **envp)
{
	t_args	*curr;
	char	*tmp;

	curr = args;
	while (curr)
	{
		if (curr->data)
		{
			tmp = curr->data;
			curr->data = put_env(curr->data, envp);
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
