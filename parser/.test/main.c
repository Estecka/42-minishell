/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 18:17:00 by abaur             #+#    #+#             */
/*   Updated: 2020/11/17 19:40:53 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "../parser.h"
#include "../../get_next_line/get_next_line.h"


/*
** Placeholder function for getting a variable's value.
*/
#define WCYAN  "\033[1;36m${"
#define WCLEAR "}\033[0m"
extern char* get_env_var(const char* name)
{
	char* result;

	result = malloc(strlen(WCYAN) + 2 + strlen(WCLEAR) + 2 + strlen(name) + 1);
	if (!result)
		return NULL;

	result[0] = '\0';
	strcat(result, WCYAN);
	strcat(result, "  ");
	strcat(result, name);
	strcat(result, "  ");
	strcat(result, WCLEAR);
	return result;
}


extern int	main(int argc, char** argv)
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
					printf("\t\t\tArg count: %u\n", expr->argc);
					if (expr->args == NULL)
						printf("No Args\n");
					else 
					{
						if (argc<2 || strcmp(argv[1], "--raw"))
							expr->args = postproc_args_all(expr->args);
						for (int j=0; expr->args[j]; j++)
							printf("\t\t\tArg[%i]: %s\n", j, expr->args[j]);
					}

					if (expr->ioarray == NULL)
						printf("\t\t\t/!\\ No redirections\n");
					else for (int j=0; expr->ioarray[j]; j++)
					{
						char* type;
						switch (expr->iotypes[j])
						{
							default: type = "??"; break;
							case punc_input:    type = "< "; break;
							case punc_truncate: type = "> "; break;
							case punc_append:   type = ">>"; break;
						}
						printf("\t\t\t%s\t%s\n", type, expr->ioarray[j]);
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
