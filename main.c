/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 15:12:00 by abaur             #+#    #+#             */
/*   Updated: 2020/10/20 12:18:41 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"
#include "builtins/builtins.h"
#include "get_next_line/get_next_line.h"
#include "envvar/envvar.h"
#include "stdrfd/stdrfd.h"

#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

static int	exec_cmd(int argc, char **argv)
{
	t_builtin	builtin;
	
	builtin = builtins_process(argv[0]);
	if (builtin)
		return(builtin(argc, argv));
	else
	{
		builtin = command_exec(argv);
		if (builtin)
			return (builtin(argc, argv));
		else
		{
			print_error("bash: ", ": command not found\n", argv[0]);
			return (127);
		}
	}
}

static int	execute_cmds_all(t_procexpr **cmdarray)
{
	int			status;
	t_procexpr	**cmd;

	status = 0;
	cmd = cmdarray;
	while (*cmd)
	{
		postproc_args_all((*cmd)->args);
		status = exec_cmd((*cmd)->argc, (*cmd)->args);
		cmd++;
	}
	if (cmdarray)
		procexpr_destroy_all(cmdarray);
	return (status);
}

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
