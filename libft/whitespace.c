/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whitespace.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 16:01:00 by abaur             #+#    #+#             */
/*   Updated: 2020/09/03 16:01:00 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

short	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f');
}

/*
** Seeks the first non-whitespace character.
** @param char* s	The string to search.
** @return char*	A pointer to the first non-whitespace character.
** 	If none are found, it will point to the \0 at the end of the string.
*/

char	*ft_skipspace(const char *s)
{
	while (*s && ft_isspace(*s))
		s++;
	return (char*)(s);
}
