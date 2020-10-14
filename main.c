/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 15:12:00 by abaur             #+#    #+#             */
/*   Updated: 2020/10/14 18:05:29 by hherin           ###   ########.fr       */
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

extern int	main(int ac, char **av, char **environ)
{
	const char* line;
	t_procexpr** cmd;
	t_procexpr*expr;
	t_builtin built;
	short gnl;

	gnl = 1;
	(void)ac;
	(void)av;
	if (!(environ = envvarinit(environ)))
	{
		printf("Init failed.\n");
		return (-1);
	}
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
				if (!(built = builtins_process(expr->args)))
					break;
				built(expr->args);
				system("leaks minishell");

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
	envvardeinit();
}