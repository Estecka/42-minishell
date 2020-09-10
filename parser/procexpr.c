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

	while (expr)
	{
		freearray((void**)expr->args);
		free(expr->args);
		freearray((void**)expr->inputs);
		free(expr->inputs);
		freearray((void**)expr->outputs);
		free(expr->outputs);
		free(expr->outtypes);
		prev = expr;
		expr = expr->pipeout;
		free(prev);
	}
}
