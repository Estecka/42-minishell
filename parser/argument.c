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
** Parses a quoted argument and appends it to the current argument.
** @param t_dynarray* chars	The character array where to store the quoted strin
** g.
** @param const char** cursor	A pointer to the first quote of the string.
*/

static void				append_quoted_string(t_dynarray *chars,
const char **cursor)
{
	char quote;

	quote = **cursor;
	(*cursor)++;
	while (**cursor && **cursor != quote)
	{
		dynappend(chars, *cursor);
		(*cursor)++;
	}
	if (**cursor == quote)
		(*cursor)++;
}

/*
** Extracts the next argument from the string, and advances the cursors accordi
** ngly.
** @param char** cursor	A pointer to where to start seeking the next argument.
** 	This pointer is moved after the end of the argument on return.
** @return char*	The found argument or NULL if none were found.
*/

static char				*next_arg(const char **cursor)
{
	t_dynarray chars;

	dyninit(&chars, sizeof(char), 8);
	*cursor = ft_skipspace(*cursor);
	while (**cursor && !ft_isspace(**cursor) && !is_punctuation(**cursor))
	{
		if (**cursor == '"' || **cursor == '\'')
			append_quoted_string(&chars, cursor);
		else
		{
			dynappend(&chars, &(**cursor));
			(*cursor)++;
		}
	}
	dynappendnull(&chars);
	if (chars.length > 1)
		return (chars.content);
	free(chars.content);
	return (NULL);
}

/*
** Breaks the command down into an array of arguments.
** @param const char* cursor	A cursor to the beginning of the command. This
**  will be moved to the next punctuation following the last argument.
** @return char**	An array of arguments. This is NULL-terminated.
*/

void					parse_cmd(t_exprbuilder *builder)
{
	char			*current_arg;
	t_punctuation	punc;

	while ((punc = next_punctuation(&builder->cursor)) != punc_end)
	{
		current_arg = next_arg(&builder->cursor);
		if (punc == punc_pipe)
			exprbuild_pipe(builder);
		if (punc == punc_none || punc == punc_pipe)
			dynappend(&builder->argsarray, &current_arg);
		else if (punc == punc_append || punc == punc_truncate)
		{
			dynappend(&builder->outarray, &current_arg);
			dynappend(&builder->typearray,
				&(short){(punc == punc_truncate) ? 1 : 0 });
		}
		else if (punc == punc_input)
			dynappend(&builder->inarray, &current_arg);
	}
}
