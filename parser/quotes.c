/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 15:02:00 by abaur             #+#    #+#             */
/*   Updated: 2020/09/30 15:02:00 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internals.h"
#include "../libft/libft.h"
#include "../dynarray/dynarray.h"



/*
** Parses a quoted argument and appends it to the current argument.
** Some escape sequences will be preserved, namely "\\" and "\$".
** @param t_dynarray* chars	The character array where to store the quoted strin
** g.
** @param const char** cursor	A pointer to the first quote of the string.
** @return bool
** 	true 	OK
** 	false	Error
*/

/*
** The single variant inserts extra \'s to form the aforementionnned escape seq
** uences.
*/

short			append_single_quote(t_dynarray *chars, const char **cursor)
{
	(*cursor)++;
	while (**cursor && **cursor != '\'')
	{
		if (**cursor == '\\' || **cursor == '$')
			dynappend(chars, "\\");
		dynappend(chars, *cursor);
		(*cursor)++;
		if (errno)
			return (0);
	}
	if (**cursor == '\'')
		(*cursor)++;
	return (1);
}

short			append_double_quote(t_dynarray *chars, const char **cursor)
{
	(*cursor)++;
	while (**cursor && **cursor != '"')
	{
		if (**cursor == '\\')
		{
			(*cursor)++;
			if (**cursor != '"')
			{
				dynappend(chars, "\\");
				if (**cursor != '\\' && **cursor != '$')
					(*cursor)--;
			}
		}
		dynappend(chars, *cursor);
		(*cursor)++;
		if (errno)
			return (0);
	}
	if (**cursor == '"')
		(*cursor)++;
	return (1);
}