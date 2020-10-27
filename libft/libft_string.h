/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_string.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 00:43:38 by abaur             #+#    #+#             */
/*   Updated: 2020/10/22 12:58:29 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_STRING_H
# define LIBFT_STRING_H

# include <stdlib.h>

/*
** Measures the lenght of the given string.
** This exludes the null terminator.
** @param const char* s	The string to measure.
** @return size_t	The length of the string.
*/

size_t	ft_strlen(const char *s);

/*
** Compare to string.
** @param const char* s1	One of the string to compare.
** @param const char* s2	The other string to compare.
** @return int	The difference between the first different characters.
** 	Returns 0 if the strings are identical.
*/

int		ft_strcmp(const char *s1, const char *s2);

/*
** Compare to string, but no further than n characters.
** @param const char* s1	One of the string to compare.
** @param const char* s2	The other string to compare.
** @param size_t n	The maximum amount of characters to compare.
** @return int	The difference between the first different characters.
** 	Returns 0 if the strings are identical.
*/

int		ft_strncmp(const char *s1, const char *s2, size_t n);

/*
** Compare to string, until a custom string terminator is found.
** Upon computing the difference, the custom terminator is treated as being equ
** al to '\0'.
** @param const char* s1	One of the string to compare.
** @param const char* s2	The other string to compare.
** @param char c	The character to use as a terminator.
** @return int	The difference between the first different characters.
** 	Returns 0 if the strings are identical.
*/

int		ft_strccmp(const char *s1, const char *s2, char terminator);

/*
** Checks wether a string contains the given character.
** @param const char* s	The string to search.
** @param char c	The character to look for.
** @return bool	True if the string contains the character, false otherwise.
*/

short	*ft_strcontain(const char *s, char c);

/*
** Locates the first occurence of a character in a string.
** @param const char* src	The string to search.
** @param char c	The character to look for.
** @return int	The index of the character, or -1 if the character was not foun
** d.
*/

int		indexof(char c, const char *src);

/*
** Locates the first occurence of a character in a string.
** @param const char* src	The string to search.
** @param char c	The character to look for.
** @return char*	A pointer to the character in the string, or NULL if the ch
** aracter was not found.
*/

char	*ft_strchr(const char *src, int c);

/*
** Locates the last occurence of a character in a string.
** @param const char* src	The string to search.
** @param char c	The character to look for.
** @return char*	A pointer to the character in the string, or NULL if the ch
** aracter was not found.
*/
char	*ft_strrchr(const char *src, int c);

/*
** Seeks the first non-whitespace character.
** @param char* s	The string to search through.
** @return char*	A pointer to the first non-whitespace character.
** 	If none are found, it will point to the string's null terminator.
*/

char	*ft_skipspace(const char *s);

/*
** Locates the first occurence of a string into another string.
** @param const char* haystack	The string to search.
** @param const char* needle	The string to look for.
** @param size_t len	The maximum amount of characters to search through.
** @return char*	A pointer to the first character of `needle` in `haystack`,
**  or NULL if none were found.
*/

char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

/*
** Duplicates the given string.
** @param const char* src	The string to duplicate
** @return char*	An allocated copy of the string. Or NULL in case of error.
*/

char	*ft_strdup(const char *src);

/*
** Duplicates an array and all of the strings int contains.
** @param const char*const* array	The array to duplicate.
** @return char**	An allocated copy of the array. Or NULL in case of error.
*/

char	**ft_strdupr(const char*const *array);

/*
** Duplicates a portion of the given string.
** @param const char* src	The string to duplicate from.
** @param unsigned int start	The index of the first character to duplicate.
** @param size_t len	The maximum size of the duplicata string.
** @return char*	An allocated copy of the string.
*/

char	*ft_substr(const char *src, unsigned int start, size_t len);

/*
** Allocates and returns a copy of the string given as argument,
** without the characters specified in the the set argument,
** at the beginning and the end of the string.
*/
/*
** Duplicates the given string, and trims a set of characters off its edges.
** @param const char* src	The string to duplicate.
** @param const char* set	A string containing the characters to be trimmed of
** f.
*/

char	*ft_strtrim(const char *src, const char *set);

/*
** Splits a string at every occurence of a character.
** TODO:
** In case of failure from ft_substr, this will not return NULL, and may cause
**  leaks.
** @param const char* src	The string to split.
** @param char	The character to use as a separator.
** @return char**	An array of all the resulting sub-strings.
** 	The array and every sub-string are allocated separately.
** 	The array is null terminated.
*/

char	**ft_split(const char *src, char separator);

/*
** Joins two string end to end.
** @param const char* s1	The first string to join.
** @param const char* s2	The next string to join.
** @return char*	An allocated copy of the newly formed string.
** 	NULL in case of error.
*/

char	*ft_strjoin(const char *s1, const char *s2);

/*
** Concatenates two strings.
** @param char*	dst	The string to be expanded.
** 	This pointer is used as a buffer. It is garanteed to be null-terminated.
** @param const char* src	The string to be appended.
** @param size_t dstsize	The maximum length of the newly formed string.
** @return size_t	The length of the newly formed string.
*/

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

/*
** Copies up to `dstsize` bytes from `src` to `dst`.
** Null terminator is garanteed and included in `dstsize`;
*/
/*
** Overwrites a string.
** @param char* dst	The string to be overwritten.
** @param const char* src	The string to be written in.
** @param size_t dst_size	The maximum length of the resulting string.
** @return size_t	The length of the resulting string.
*/

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

/*
** Creates a new string by tranforming another string.
** @param const char* src	The string to be transformed
** @param function* f	A function that will be applied to every character from
**  the source string in order.
** It takes as parameter the index of the character, its value, and returnd the
**  transformed character.
** @return	The resulting string, or NULL in case of error.
*/

char	*ft_strmapi(const char *src, char (*f)(unsigned int, char));

#endif
