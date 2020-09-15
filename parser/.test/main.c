/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 18:17:00 by abaur             #+#    #+#             */
/*   Updated: 2020/08/31 18:17:00 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "../parser.h"
#include "../../get_next_line/get_next_line.h"

extern int	main()
{
	const char* line;
	t_procexpr** cmd;
	short gnl;

	gnl = 1;
	while(0 < gnl)
	{
		cmd = NULL;
		write(1, "\n> ", 3);
		gnl = get_next_line(0, (char**)&line);
		printf("%s\n", line);
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
				printf("\tCommand #%i\n", i);
				for(t_procexpr *expr=cmd[i]; expr; expr=expr->pipeout)
				{
					printf("\t\tProcess [%p]\n", expr);
					printf("\t\t\tPipe IN:  [%p]\n", expr->pipein);
					if (expr->args == NULL)
						printf("No Args\n");
					else for (int j=0; expr->args[j]; j++)
						printf("\t\t\tArg[%i]: %s\n", j, expr->args[j]);

					if (expr->inputs == NULL)
						printf("\t\t\t/!\\No Inputs\n");
					else for (int j=0; expr->inputs[j]; j++)
						printf("\t\t\t< \t%s\n", expr->inputs[j]);

					if (expr->outputs == NULL)
						printf("\t\t\t/!\\ No Outputs\n");
					else for (int j=0; expr->outputs[j]; j++)
					{
						char* type = expr->outtypes[j] ? "> " : ">>";
						printf("\t\t\t%s\t%s\n", type, expr->outputs[j]);
					}
					printf("\t\t\tPipe OUT: [%p]\n", expr->pipeout);
				}
			}
		}

		if (cmd)
		{
			for (t_procexpr** e=cmd; *e; e++)
				procexpr_destroy(*e);
			free(cmd);
		}

		free((void*)line);

		printf("\tgnl = %d\n\n", gnl);
		if (gnl == 0)
			break;
	}
}
