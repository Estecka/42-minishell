/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 16:23:00 by abaur             #+#    #+#             */
/*   Updated: 2020/08/30 16:23:00 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internals.h"
#include "../get_next_line/get_next_line.h"

/*
** Breaks a string down into an array of arguments.
** @param const char* line	The string to break down.
** @return char**	An array of arguments.
*/

static char	**split_args(const char *line)
{
	t_dynarray	args;
	char		*current_arg;

	dyninit(&args, sizeof(char*), 8);
	while (peek_argument(line))
	{
		current_arg = next_arg(&line);
		dynappend(&args, &current_arg);
	}
	dynappend(&args, &(char*){NULL});
	return (char**)(args.content);
}

extern int	get_next_expr(t_cmdexpr *expr, char **line)
{
	int		err;

	err = get_next_line(0, line);
	if (err < 0)
		return (err);
	*expr = (t_cmdexpr){ 0 };
	if (*line)
		expr->args = (const char**)split_args(*line);
	return (err);
}
