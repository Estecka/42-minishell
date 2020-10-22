/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 15:12:00 by abaur             #+#    #+#             */
/*   Updated: 2020/10/22 10:33:20 by abaur            ###   ########.fr       */
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
static char			*g_currentline = NULL;
static t_procexpr	**g_currentexpr = NULL;

extern void clean_exit(int status)
{
	envvardeinit();
	if (g_currentline)
		free(g_currentline);
	if (g_currentexpr)
		procexpr_destroy_all(g_currentexpr);
	write(2, "exit\n", 5);
	exit(status);
}

static int	shell_main(void)
{
	short		gnl;

	gnl = 1;
	while (0 < gnl)
	{
		write(0, "> ", 2);
		gnl = get_next_line(0, (char**)&g_currentline);
		g_currentexpr = get_next_cmdline(g_currentline);
		if (errno || !g_currentexpr)
		{
			ft_putstr_fd("Parsing failed unexpectedly: ", 2);
			ft_putendl_fd(strerror(errno), 2);
		}
		else
		{
			execute_cmds_all(g_currentexpr);
			g_currentexpr = NULL;
		}
		if (g_currentline)
		{
			free(g_currentline);
			g_currentline = NULL;
		}
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
	clean_exit (status);
}
