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
** Checks whether the next non-whitespace element of a string is an argument.
** @param char* s	The string to search.
** @return bool
** 	true 	The next element of the command is an argument.
** 	false	The next element is punctuation, or the end of the string.
*/

static short	peek_argument(const char *s)
{
	s = ft_skipspace(s);
	return (*s && !is_punctuation(*s));
}

/*
** Parses a quoted argument and appends it to the current argument.
** @param t_dynarray* chars	The character array where to store the quoted strin
** g.
** @param const char** cursor	A pointer to the first quote of the string.
*/

static void		append_quoted_string(t_dynarray *chars, const char **cursor)
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

static char		*next_arg(const char **cursor)
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

void	parse_args(t_exprbuilder *builder)
{
	char		*current_arg;

	while (peek_argument(builder->cursor))
	{
		current_arg = next_arg(&builder->cursor);
		dynappend(&builder->argsarray, &current_arg);
	}
	while (*builder->cursor && !is_punctuation(*builder->cursor))
		builder->cursor++;
}
