/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procexpr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 18:01:00 by abaur             #+#    #+#             */
/*   Updated: 2020/10/26 13:10:24 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internals.h"

extern int	procexpr_pipelen(t_procexpr *expr)
{
	int	len;

	len = 0;
	while (expr)
	{
		len++;
		expr = expr->pipeout;
	}
	return (len);
}

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

extern void	procexpr_destroy_all(t_procexpr **exprarray)
{
	t_procexpr **expr;

	expr = exprarray;
	while (*expr)
	{
		procexpr_destroy(*expr);
		expr++;
	}
	free(exprarray);
}

extern void	procexpr_destroyarrayn(t_procexpr **array, size_t length)
{
	while (length--)
	{
		if (*array)
			procexpr_destroy(*array);
		array++;
	}
}
