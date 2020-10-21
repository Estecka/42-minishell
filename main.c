/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 15:12:00 by abaur             #+#    #+#             */
/*   Updated: 2020/10/21 15:55:42 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "libft/libft.h"
#include "parser/parser.h"
#include "get_next_line/get_next_line.h"
#include "envvar/envvar.h"
#include "stdrfd/stdrfd.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char		g_prev_status = 0;

static int	shell_main(void)
{
	char		*line;
	t_procexpr	**cmd;
	short		gnl;

	gnl = 1;
	while (0 < gnl)
	{
		write(0, "> ", 2);
		gnl = get_next_line(0, (char**)&line);
		cmd = get_next_cmdline(line);
		if (errno || !cmd)
		{
			ft_putstr_fd("Parsing failed unexpectedly: ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putchar_fd('\n', 1);
		}
		else
			execute_cmds_all(cmd);
		if (line)
			free(line);
	}
	return (0);
}

static int	subprocess_main(int argc, char** argv)
{
	int	status;

	argv = ft_strdupr((const char**)argv);
	if (!argv)
		return (EXIT_FAILURE);
	status = exec_cmd(argc, argv);
	freearray((void**)argv);
	free(argv);
	return (status);
}

extern int	main(int argc, char **argv, char **environ)
{
	int status;

	if (!envvarinit(environ))
		return (errno | (0 & write(2, "Environnement init failed.\n", 14)));
	if (!backup_stdrfd())
		return (errno | (0 & write(2, "Stdrfd init failed.\n", 14)));
	status = 0;
	if (argc > 1)
		status = subprocess_main(argc - 1, argv + 1);
	else
		status = shell_main();
	envvardeinit();
	return (status);
}
