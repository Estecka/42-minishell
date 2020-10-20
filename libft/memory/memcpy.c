/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 19:01:01 by abaur             #+#    #+#             */
/*   Updated: 2020/10/17 19:02:39 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

extern void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((char*)dst)[i] = ((char*)src)[i];
		i++;
	}
	return (dst);
}

extern void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*fro;
	unsigned char	*to;

	fro = (unsigned char*)src;
	to = (unsigned char*)dst;
	i = 0;
	while (i < n)
	{
		to[i] = fro[i];
		if (to[i] == (unsigned char)c)
			return (&(to[i + 1]));
		i++;
	}
	return (NULL);
}

extern void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*fro;
	char	*to;
	size_t	i;
	short	sign;

	if (!dst && !src)
		return (NULL);
	to = (char*)dst;
	fro = (char*)src;
	sign = dst < src ? +1 : -1;
	i = dst < src ? 0 : len - 1;
	while (i < len)
	{
		to[i] = fro[i];
		if (sign < 0 && i == 0)
			break ;
		i += sign;
	}
	return (dst);
}
