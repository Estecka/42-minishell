/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internals.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 15:48:00 by abaur             #+#    #+#             */
/*   Updated: 2020/09/03 15:48:00 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internals.h"

/*
** Checks whether a character counts as punctuation for a command.
** These characters are '>', '<', '|', and ';'.
** Quotes and double quotes do not count as punctuation, as they are part of st
** andard arguments.
** @param char c	The character to evaluate.
** @return bool
** 	true 	The character is punctuation.
** 	false	The character is not punctuation.
*/

short	is_punctuation(char c)
{
	return (c == '>' || c == '<' || c == '|' || c == ';');
}

/*
** Checks whether the next non-whitespace element of a string is an argument.
** @param char* s	The string to search.
** @return bool
** 	true 	The next element of the command is an argument.
** 	false	The next element is punctuation, or the end of the string.
*/

short	peek_argument(const char *s)
{
	s = ft_skipspace(s);
	return (*s  && !is_punctuation(*s));
}
