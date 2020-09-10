/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procexpr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 18:01:00 by abaur             #+#    #+#             */
/*   Updated: 2020/09/05 18:01:00 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internals.h"

extern void	procexpr_destroy(t_procexpr *expr)
{
	t_procexpr	*prev;
	char		**args;

	while (expr)
	{
		args = expr->args - 1;
		while (*++args)
			free(*args);
		free(expr->args);
		args = expr->inputs - 1;
		while (*++args)
			free(*args);
		free(expr->inputs);
		args = expr->outputs - 1;
		while (*++args)
			free(*args);
		free(expr->outputs);
		free(expr->outtypes);
		prev = expr;
		expr = expr->pipeout;
		free(prev);
	}
}
