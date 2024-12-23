/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksorokol <ksorokol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 12:43:38 by ksorokol          #+#    #+#             */
/*   Updated: 2024/12/23 16:57:04 by ksorokol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"

static int	sh_isnumber(char *str);

int	_exit_(char **argv, t_ctx ctx, int std_backup[2])
{
	char	*str;
	int		i[2];

	i[0] = sh_pstr_size (argv);
	if (i[0] > 1)
		i[1] = sh_isnumber (argv[1]);
	else
		i[1] = EXIT_SUCCESS;
	if (i[0] > 2 && i[1])
		return (sh_err ("exit: too many arguments\n"), 1);
	write (1, "exit\n", 5);
	if (std_backup)
		close_pipe(std_backup);
	if (i[0] == 1)
		run_exit (argv, ctx, EXIT_SUCCESS, NULL);
	else if (i[0] == 2 && i[1])
		run_exit (argv, ctx, ft_atoi (argv[1]), NULL);
	str = sh_strjoin ("exit: ", argv[1]);
	str = sh_strjoin_free (str, ": numeric argument required", 1);
	sh_err(str);
	run_exit (argv, ctx, 2, str);
	return (0);
}

static int	sh_isnumber(char *str)
{
	size_t	idx;

	idx = 0;
	if (str[idx] == '+' || str[idx] == '-' )
		idx++;
	while (str[idx])
	{
		if (!ft_isdigit (str[idx]))
			return (0);
		idx++;
	}
	return (1);
}
