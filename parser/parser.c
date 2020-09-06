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
** Parses the next command from a string, and moves the cursor accordingly.
** @param char** cursor	A pointer to the string to search. This cursor will be
**  moved to the beginning of the following command.
** @return t_cmdexpr*	The resulting command expression, or NULL if none were
**  found.
*/

static t_cmdexpr	*get_next_cmd(const char **cursor)
{
	t_exprbuilder	builder;

	*cursor = ft_skipspace(*cursor);
	if (!**cursor)
		return (NULL);
	exprbuild_init(&builder, *cursor);
	parse_args(&builder);
	*cursor = builder.cursor;
	while (**cursor)
		if (*((*cursor)++) == ';')
			break ;
	return (exprbuild_complete(&builder));
}

extern t_cmdexpr	**get_next_cmdline(const char *line)
{
	t_dynarray	commands;
	t_cmdexpr	*latest;

	dyninit(&commands, sizeof(t_cmdexpr*), 1);
	while ((latest = get_next_cmd(&line)))
		dynappend(&commands, &latest);
	dynappendnull(&commands);
	return (t_cmdexpr**)(commands.content);
}
