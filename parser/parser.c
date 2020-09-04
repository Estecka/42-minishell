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

static char	**split_args_legacy(const char *line)
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

extern int	get_next_expr_legacy(t_cmdexpr *expr, char **line)
{
	int		err;

	err = get_next_line(0, line);
	if (err < 0)
		return (err);
	*expr = (t_cmdexpr){ 0 };
	if (*line)
		expr->args = split_args_legacy(*line);
	return (err);
}

/*
** Parses the next command from a string, and moves the cursor accordingly.
** @param char** cursor	A pointer to the string to search. This cursor will be
**  moved to the beginning of the following command.
** @return t_cmdexpr*	The resulting command expression, or NULL if none were
**  found.
*/

static t_cmdexpr	*get_next_cmd(const char **cursor)
{
	t_cmdexpr *result;

	*cursor = ft_skipspace(*cursor);
	if (!**cursor)
		return (NULL);
	if (!(result = malloc(sizeof(t_cmdexpr))))
		return (NULL);
	result->args = parse_args(cursor);

	// parse io()

	while(**cursor)
		if (*((*cursor)++) == ';')
			break;
	return (result);
}

extern t_cmdexpr	**get_next_cmdline(const char *line)
{
	t_dynarray	commands;
	t_cmdexpr	*latest;

	dyninit(&commands, sizeof(t_cmdexpr*), 1);
	while ((latest = get_next_cmd(&line)))
		dynappend(&commands, &latest);
	dynappend(&commands, &(void*){NULL});

	return (t_cmdexpr**)(commands.content);
}
