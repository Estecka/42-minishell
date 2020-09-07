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

#include "../parser.h"
#include "../../get_next_line/get_next_line.h"

static void	destroy_expr(t_cmdexpr *expr)
{
	while (expr)
	{
		for(char** arg=expr->args; *arg; arg++)
			free(*arg);
		free(expr->args);

		// Note for later:
		// Triple free on piped expressions happening in the for below.

		for (t_ioredir* in=expr->inputs; in->type; in++)
			free(in->target.path);
		free(expr->inputs);

		for (t_ioredir* out=expr->outputs; out->type; out++)
			free(out->target.path);
		free(expr->outputs);

		free(expr);
		expr = NULL;
	}
}

extern int	main()
{
	const char* line;
	t_cmdexpr** expr;
	short gnl;

	gnl = 1;
	while(0 < gnl)
	{
		expr = NULL;
		write(1, "\n> ", 3);
		gnl = get_next_line(0, (char**)&line);
		printf("%s\n", line);
		expr = get_next_cmdline(line);

		for (int i=0; expr[i]; i++)
		{
			printf("\tCommand #%i [%p]\n", i, expr + i);

			if (expr[i]->args == NULL)
				printf("No Args\n");
			else for (int j=0; expr[i]->args[j]; j++)
				printf("\t\tArg[%i]: %s\n", j, expr[i]->args[j]);

			if (expr[i]->inputs == NULL)
				printf("\t\t/!\\No Inputs\n");
			else for (int j=0; expr[i]->inputs[j].type; j++)
			{
				switch (expr[i]->inputs[j].type)
				{
					default: printf("\t\t{%2d}\t%p", expr[i]->inputs[j].type, expr[i]->inputs[j].target.expr); break;
					case io_truncate: printf("\t\t< \t%s\n", expr[i]->inputs[j].target.path); break;
					case io_pipe:     printf("\t\t| \t[%p]\n", expr[i]->inputs[j].target.expr); break;
				}
			}

			if (expr[i]->outputs == NULL)
				printf("\t\t/!\\ No Outputs\n");
			else for (int j=0; expr[i]->outputs[j].type; j++)
			{
				switch (expr[i]->outputs[j].type)
				{
					default: printf("\t\t{%2d}\t%p", expr[i]->outputs[j].type, expr[i]->outputs[j].target.expr); break;
					case io_truncate: printf("\t\t> \t%s\n", expr[i]->outputs[j].target.path); break;
					case io_append:   printf("\t\t>>\t%s\n", expr[i]->outputs[j].target.path); break;
					case io_pipe:     printf("\t\t| \t[%p]\n", expr[i]->outputs[j].target.expr); break;
				}
			}
		}

		printf("\tgnl = %d\n\n", gnl);

		for (t_cmdexpr** e=expr; *e; e++)
			destroy_expr(*e);
		free(expr);
		free((void*)line);

		if (gnl == 0)
			break;
	}
}
