/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:17:50 by abaur             #+#    #+#             */
/*   Updated: 2020/11/15 16:45:15 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_string.h"

#include <stdlib.h>

extern size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*(s++))
		len++;
	return (len);
}

extern size_t	ft_ptrlen(const void **array)
{
	size_t	len;

	len = 0;
	while (*(array++))
		len++;
	return (len);
}

extern char		**ft_split(char const *s, char c)
{
	char				**results;
	unsigned int		wordcount;
	int					i;
	int					start;

	wordcount = 1;
	i = -1;
	while (s && s[++i])
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			wordcount++;
	if (!(results = (char**)malloc(sizeof(char*) * wordcount)))
		return (NULL);
	i = -1;
	start = 0;
	wordcount = 0;
	while (s && s[++i])
		if (s[i] != c)
		{
			if (i == 0 || s[i - 1] == c)
				start = i;
			if (s[i + 1] == c || s[i + 1] == '\0')
				results[wordcount++] = ft_substr(s, start, i + 1 - start);
		}
	results[wordcount] = NULL;
	return (results);
}

extern char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	char	*result;

	if (!s)
		return (NULL);
	len = 0;
	while (s[len])
		len++;
	result = (char*)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	while (--len >= 0)
		result[len] = f ? f(len, s[len]) : 0;
	return (result);
}
