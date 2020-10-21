/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 15:02:00 by abaur             #+#    #+#             */
/*   Updated: 2020/10/21 13:35:59 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internals.h"
#include "../libft/libft.h"
#include "../dynarray/dynarray.h"



/*
** Crawls through a quoted argument and appends it to the current argument.
** @param t_dynarray* chars	The character array where to store the quoted strin
** g.
** @param const char** cursor	A pointer to the first quote of the string.
** 	This cursor will point to the terminating quote on success.
** @return bool
** 	true 	OK
** 	false	Error
*/

short			append_single_quote(t_dynarray *chars, const char **cursor)
{
	if (!dynappend(chars, "\'"))
		return (0);
	(*cursor)++;
	while (**cursor)
	{
		dynappend(chars, &**cursor);
		(*cursor)++;
		if (errno)
			return (0);
		if (**cursor == '\'')
			break ;
	}
	return (1);
}

short			append_double_quote(t_dynarray *chars, const char **cursor)
{
	short	escaped;

	if (!dynappend(chars, "\""))
		return (0);
	(*cursor)++;
	while (**cursor)
	{
		if ((escaped = (**cursor == '\\' && *(*cursor + 1))))
		{
			dynappendn(chars, &**cursor, 2);
			(*cursor)++;
		}
		else
			dynappend(chars, &**cursor);
		(*cursor)++;
		if (errno)
			return (0);
		if (!escaped && **cursor == '\"')
			break ;
	}
	return (1);
}