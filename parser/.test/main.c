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

extern int	main()
{
	t_cmdexpr expr;
	short err;

	err = 1;
	while(0 < err)
	{
		expr = (t_cmdexpr){ 0 };
		write(1, "\n>", 2);
		err = get_next_expr(&expr);
		if (expr.args != NULL)
		{
			const char** cursor = expr.args;
			do {
				printf("Arg: %s\n", *cursor);
				cursor++;
			}
			while (*cursor != NULL);
		}
		printf("rvalue = %i\n", err);
	}
}
