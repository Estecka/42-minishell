/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 15:02:00 by abaur             #+#    #+#             */
/*   Updated: 2020/10/21 10:38:46 by abaur            ###   ########.fr       */
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
		if (*(*cursor - 1) == '\'')
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
			*cursor += 2;
		}
		else
		{
			dynappend(chars, &**cursor);
			*cursor += 1;
		}
		if (errno)
			return (0);
		if (!escaped && *(*cursor - 1) == '\"')
			break ;
	}
	return (1);
}