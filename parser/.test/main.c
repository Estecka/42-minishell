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

		// for (input in expr->inputs)
		// 	free(input);
		free(expr->inputs);

		// for (output in expr->outputs)
		// 	free(output);
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
			printf("\tCommand #%i\n", i);
			if (expr[i]->args == NULL)
				printf("No Args\n");
			else for (int j=0; expr[i]->args[j]; j++)
				printf("\t\tArg[%i]: %s\n", j, expr[i]->args[j]);
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
