/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 15:12:00 by abaur             #+#    #+#             */
/*   Updated: 2020/10/09 12:08:48 by hherin           ###   ########.fr       */
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

static int	builtin_main(int argc, char **argv)
{
	for (int i=0; i<argc; i++)
		printf("%s\n", argv[i]);
	return (0);
}

static int	shell_main()
{
	const char* line;
	t_procexpr** cmd;
	t_procexpr*expr;
	short gnl;

	gnl = 1;
	while(0 < gnl)
	{
		cmd = NULL;
		write(2, "> ", 2);
		gnl = get_next_line(0, (char**)&line);
		cmd = get_next_cmdline(line);

		if (errno)
			printf ("\tParsing failed with errno : %d\n", errno);
		else if (!cmd)
			printf("\tParsing failed with no error.\n");
		else if (!cmd[0])
			printf("\tParsing yielded an empty array with no error.\n");
		else
		{
			for (int i=0; cmd[i]; i++)
			{
				expr = cmd[i];
				clear_array(expr->args);
				if (expr->args == NULL)
					printf("No Args\n");
				builtins_process(expr->args, g_envarray.content);
			}
		
		}
		if (cmd) // libere memoire
		{
			for (t_procexpr** e=cmd; *e; e++)
				procexpr_destroy(*e);
			free(cmd);
		}
		free((void*)line);


		if (gnl == 0)
			break;
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
