/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 16:23:00 by abaur             #+#    #+#             */
/*   Updated: 2020/11/19 16:54:23 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "parser_internals.h"
#include "../get_next_line/get_next_line.h"

/*
** # get_next_cmd abortion procedure
**
** exprbuild_init() and parse_cmd() are the only possible points of failure. Bo
** th are expected to leave the exprbuilder in a state such as exprbuild_abort(
** ) can safely destroy every dangling pointers.
*/

/*
** Parses the next command from a string, and moves the cursor accordingly.
** @param char** cursor	A pointer to the string to search.
** 	This cursor will be moved to the beginning of the following command. Its va
** lue is undefined in case of error.
** @return t_procexpr*	The resulting command expression, NULL if none were fou
** nd or an error occured. In case of error, errno will be set.
*/

static t_procexpr	*get_next_cmd(const char **cursor)
{
	t_exprbuilder	builder;

	builder = (t_exprbuilder){0};
	*cursor = ft_skipspace(*cursor);
	if (!**cursor)
		return (NULL);
	if (exprbuild_init(&builder, *cursor) && parse_cmd(&builder)
		&& exprbuild_complete(&builder))
	{
		*cursor = builder.cursor;
		return (builder.firstproc);
	}
	exprbuild_abort(&builder);
	return (NULL);
}

/*
** # get_next_cmdline abortion procedure
**
** ## Scenario 1: dyninit fails
** No resources are allocated, and nothing needs to be freed.
**
** ## Scenario 2: get_next_cmd fails.
** get_next_cmd shall free its own pointers before returning, so `latest` will
**  be NULL and shalls not be minded.
** `commands` may have been initialized and contain valid command expressions,
**  which may be fully freed using `procexp_destroy()`.
**
** ## Scenario 3: dynexpand fails
** As long as dynexpand succeeds, the following dynappend can not fails.
** `command` shall be handled with the same requirement as when get_next_cmd fa
** ils.
** dynappend will not be called, thus `latest` will contain a valid command exp
** ression that is not listed in `commands`.
** dynnapend may still safely be called even if dynexpand fails, but should not
**  generate any effects that needs to be minded.
*/

extern t_procexpr	**get_next_cmdline(const char *line)
{
	t_dynarray	commands;
	t_procexpr	*latest;

	errno = 0;
	if (dyninit(&commands, sizeof(t_procexpr*), 1, 1))
		while ((latest = get_next_cmd(&line)) && dynexpand(&commands, 1))
			dynappend(&commands, &latest);
	if (errno && latest)
		procexpr_destroy(latest);
	if (errno && commands.content)
	{
		procexpr_destroyarrayn(commands.content, commands.length);
		free(commands.content);
	}
	return (t_procexpr**)(errno ? NULL : commands.content);
}
