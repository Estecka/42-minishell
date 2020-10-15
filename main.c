/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 15:12:00 by abaur             #+#    #+#             */
/*   Updated: 2020/10/15 11:45:52 by hherin           ###   ########.fr       */
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

static void	print_error(char *args)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(args, 2);
	ft_putstr_fd(": command not found\n", 2);
}

static int	builtin_main(int argc, char **argv)
{
	t_builtin builtin;
	
	builtin = builtins_process(argv[0]);
	if (builtin)
		return(builtin(argc, argv));
	else
	{
		print_error(argv[0]);
		return (127);	
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
		status = builtin_main((*cmd)->argc, (*cmd)->args);
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
		builtin_main(argc - 1, argv + 1);
	else
		shell_main();
	envvardeinit();
	return (0);
}
