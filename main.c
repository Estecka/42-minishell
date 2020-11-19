/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 15:12:00 by abaur             #+#    #+#             */
/*   Updated: 2020/11/19 18:09:04 by abaur            ###   ########.fr       */
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

char				g_prev_status = 0;
short				g_is_subprocess = 0;
static char			*g_currentline = NULL;
static t_procexpr	**g_currentexpr = NULL;
short				g_prompt = 0;

extern int			clean_exit(int status)
{
	envvardeinit();
	if (g_currentline)
		free(g_currentline);
	if (g_currentexpr)
		procexpr_destroy_all(g_currentexpr);
	if (!g_is_subprocess)
		write(2, "exit\n", 5);
	exit(status);
}

static int			shell_main(void)
{
	short		gnl;

	gnl = 1;
	while (0 < gnl)
	{
		g_prompt = 0 & write(0, "> ", 2);
		gnl = get_next_line(0, (char**)&g_currentline);
		g_prompt = 1;
		g_currentexpr = get_next_cmdline(g_currentline);
		if (errno == EINVAL)
			ft_putstr_fd("Invalid syntax.\n", 2);
		else if (errno || !g_currentexpr)
			ft_putendl_fd(strerror(errno), 2);
		else
		{
			g_prev_status = execute_cmds_all(g_currentexpr);
			g_currentexpr = NULL;
		}
		if (g_currentline)
		{
			free(g_currentline);
			g_currentline = NULL;
		}
	}
	return (g_prev_status);
}

static int			subprocess_main(int argc, char **argv)
{
	argv = ft_strdupr((const char**)argv);
	if (!argv)
		return (EXIT_FAILURE);
	g_prev_status = exec_cmd(argc, argv);
	freearray((void**)argv);
	free(argv);
	return (g_prev_status);
}

extern int			main(int argc, char **argv, char **environ)
{
	if (!(*environ))
	{
		if (!envnulinit())
			return (errno | (0 & write(2, "Environnement init failed.\n", 14)));
	}
	else if (!envvarinit(environ))
		return (errno | (0 & write(2, "Environnement init failed.\n", 14)));
	if (!backup_stdrfd())
		return (errno | (0 & write(2, "Stdrfd init failed.\n", 14)));
	shell_level();
	if (!signal_exec())
		return (errno | (0 & write(2, "Could not set signal handler\n", 29)));
	if (argc > 1)
		g_prev_status = subprocess_main(argc - 1, argv + 1);
	else
		g_prev_status = shell_main();
	clean_exit(g_prev_status);
}
