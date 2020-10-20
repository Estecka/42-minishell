/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:22:37 by abaur             #+#    #+#             */
/*   Updated: 2020/10/17 19:13:29 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_char.h"

#include <stdlib.h>

extern short	ft_strcontain(const char *s, char c)
{
	while (s && *s != '\0')
		if (*(s++) == c)
			return (1);
	return (0);
}

extern int		indexof(char c, const char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (-1);
}

extern char		*ft_strchr(const char *s, int c)
{
	while (1)
	{
		if (*s == c)
			return ((char*)s);
		if (!*s)
			return (NULL);
		s++;
	}
}

extern char		*ft_strrchr(const char *s, int c)
{
	const char *result;

	result = NULL;
	while (1)
	{
		if (*s == (char)c)
			result = s;
		if (!*s)
			break ;
		s++;
	}
	return ((char*)result);
}

extern char		*ft_skipspace(const char *s)
{
	while (*s && ft_isspace(*s))
		s++;
	return (char*)(s);
}
