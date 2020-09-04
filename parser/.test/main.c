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
#include <stdio.h>

#include "../parser.h"
#include "../../get_next_line/get_next_line.h"

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
		if (gnl == 0)
			break;
	}
}
