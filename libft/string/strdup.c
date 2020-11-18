/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 11:58:31 by abaur             #+#    #+#             */
/*   Updated: 2020/11/15 16:45:36 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_string.h"
#include "../libft_malloc.h"

#include <stdlib.h>

extern char	*ft_strdup(const char *s1)
{
	size_t		len;
	char		*result;

	len = 0;
	while (s1[len] != '\0')
		len++;
	result = (char*)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	while (len--)
	{
		result[len] = s1[len];
		if (len == 0)
			break ;
	}
	return (result);
}

extern char	**ft_strdupr(const char*const *array)
{
	size_t	len;
	char	**result;

	len = 0;
	while (array[len] != NULL)
		len++;
	result = malloc(sizeof(char*) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = NULL;
	while (len--)
	{
		result[len] = ft_strdup(array[len]);
		if (!result[len])
		{
			freearray((void**)result);
			free(result);
			return (NULL);
		}
		if (len == 0)
			break ;
	}
	return (result);
}

extern char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	end;
	char			*result;
	unsigned int	i;

	if (!s)
		return (NULL);
	end = 0;
	while (s[end] != '\0' && end < (start + len))
		end++;
	len = start < end ? end - start : 0;
	result = (char*)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	i = -1;
	while (++i < len)
		result[i] = s[i + start];
	result[len] = '\0';
	return (result);
}

extern char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		len;
	int			i;
	char		*result;
	const char	*cursor;

	len = 1;
	cursor = s1;
	while (s1 && *(cursor++) != '\0')
		len++;
	cursor = s2;
	while (s2 && *(cursor++) != '\0')
		len++;
	result = (char*)malloc(sizeof(char) * len);
	if (!result)
		return (NULL);
	i = 0;
	cursor = s1;
	while (s1 && *cursor)
		result[i++] = *(cursor++);
	cursor = s2;
	while (s2 && *cursor)
		result[i++] = *(cursor++);
	result[len - 1] = '\0';
	return (result);
}

extern char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	unsigned int	end;
	unsigned int	i;
	short			started;

	started = 0;
	start = 0;
	end = 0;
	i = -1;
	while (s1 && s1[++i] != '\0')
		if (!ft_strcontain(set, s1[i]))
		{
			if (!started)
			{
				started = 1;
				start = i;
			}
			end = i;
		}
	if (started)
		return (ft_substr(s1, start, end - start + 1));
	else
		return (ft_strdup(""));
}
