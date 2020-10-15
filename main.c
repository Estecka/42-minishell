/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 15:12:00 by abaur             #+#    #+#             */
/*   Updated: 2020/10/15 17:53:56 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"
#include "builtins/builtins.h"
#include "get_next_line/get_next_line.h"
#include "envvar/envvar.h"
#include <sys/errno.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

static void	print_error(char *args)
{
	printf("HOME %s\n", strerror(errno));
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(args, 2);
	ft_putstr_fd(": command not found\n", 2);
}

static int	exec_cmd(int argc, char **argv) //else if execve + changer nom
{
	t_builtin	builtin;
	struct stat	*buf;
	
	buf = NULL;
	builtin = builtins_process(argv[0]);
	if (builtin)
		return(builtin(argc, argv));
	else
	{
		builtin = command_exec();
		if ((stat(argv[0], buf)))
			return (builtin(argc, argv));
		else
		{
			print_error(argv[0]);
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
			printf("\tParsing failed with errno : %d\n", errno);
		else
			execute_cmds_all(cmd);
		if (line)
			free(line);
	}
	return (0);
}

extern int	main(int argc, char **argv, char **environ)
{
	if (!envvarinit(environ))
	{
		write(2, "Init failed.\n", 14);
		return (errno);
	}
	if (argc > 1)
		exec_cmd(argc - 1, argv + 1);
	else
		shell_main();
	envvardeinit();
	return (0);
}
