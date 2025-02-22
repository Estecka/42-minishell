/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 16:23:00 by abaur             #+#    #+#             */
/*   Updated: 2020/11/09 15:31:55 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internals.h"
#include "../libft/libft.h"
#include "../dynarray/dynarray.h"

/*
** Extracts the next punctuation from the command line.
** @param char** cursor	A cursor to the string to search.
** 	This will be moved to the first non-whitespace following the punctuation.
** @return t_punctuation	The matching punctuation.
*/

static t_punctuation	next_punctuation(const char **cursor)
{
	t_punctuation r;

	*cursor = ft_skipspace(*cursor);
	if (!**cursor || **cursor == ';')
		r = punc_end;
	else if (**cursor == '|')
		r = punc_pipe;
	else if (**cursor == '<')
		r = punc_input;
	else if (**cursor == '>')
	{
		if (*(*cursor + 1) == '>')
		{
			r = punc_append;
			++*cursor;
		}
		else
			r = punc_truncate;
	}
	else
		r = punc_none;
	if (**cursor && r != punc_none)
		*cursor = ft_skipspace((*cursor) + 1);
	return (r);
}

/*
** Extracts the next argument from the string, and advances the cursors accordi
** ngly.
** No dangling pointers will be created in case of error, errno will also be se
** t.
** @param char** cursor	A pointer to where to start seeking the next argument.
** 	This pointer is moved after the end of the argument on return.
** @return char*	The found argument, NULL if none were found or an error occu
** red
** Arguments are returned as-is, no interpretation whatsoever is made.
*/

static char				*next_arg(const char **cursor)
{
	t_dynarray chars;

	*cursor = ft_skipspace(*cursor);
	if (!**cursor || is_punctuation(**cursor)
		|| !dyninit(&chars, sizeof(char), 16, 1))
		return (NULL);
	while (**cursor && !ft_isspace(**cursor) && !is_punctuation(**cursor))
	{
		if (**cursor == '\'')
			append_single_quote(&chars, cursor);
		else if (**cursor == '"')
			append_double_quote(&chars, cursor);
		else if (**cursor == '\\')
			dynappendn(&chars, (*cursor)++, 2);
		else
			dynappend(&chars, &(**cursor));
		if (errno)
		{
			free(chars.content);
			return (NULL);
		}
		(*cursor)++;
	}
	return (chars.content);
}

/*
** # parse_cmd abortion procedure
**
** The possible points of failure are exprbuild_pipe(), dynexpand(), and next_a
** rg().
** Dynexpand guarantees that the following dynappend()'s cannot fail, thus all
**  points of failures are centralized at the very beginning of each loop guara
** nteeing that no dangling pointers can be created before a failure.
*/

/*
** Parses a single command. (';'-terminated)
** @param t_exprbuilder* builder	The builder where to store the parsed comma
** nd.
** In case of error, the builder should then be cleansed withe exprbuild_abort.
** @return bool
** 	true 	OK
** 	false	Error
*/

short					parse_cmd(t_exprbuilder *builder)
{
	char			*current_arg;
	t_punctuation	punc;

	while ((punc = next_punctuation(&builder->cursor)) != punc_end)
	{
		if (!dynexpand(&builder->argsarray, 1) || !dynexpand(&builder->ioarray,
1) || !dynexpand(&builder->typearray, 1))
			return (0);
		if (punc == punc_pipe && !exprbuild_pipe(builder))
			return (0);
		if ((current_arg = next_arg(&builder->cursor)))
		{
			if (punc == punc_none || punc == punc_pipe)
				dynappend(&builder->argsarray, &current_arg);
			else if (punc == punc_append || punc == punc_truncate
				|| punc == punc_input)
				(void)(dynappend(&builder->ioarray, &current_arg)
					&& dynappend(&builder->typearray, &punc));
		}
		else if (errno || punc != punc_none)
			return (0 & (errno ? 0 : (errno = EINVAL)));
	}
	return (1);
}
