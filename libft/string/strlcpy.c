/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:44:47 by abaur             #+#    #+#             */
/*   Updated: 2020/10/17 15:45:25 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

extern size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (!src || !dst)
		return (0);
	i = 0;
	while (1)
	{
		if (i == dstsize - 1)
			dst[i] = '\0';
		else if (i < dstsize)
			dst[i] = src[i];
		if (src[i] == '\0')
			return (i);
		i++;
	}
}

extern size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (dst[i] && i < dstsize)
		i++;
	j = 0;
	while (1)
	{
		if (i == dstsize - 1)
			dst[i] = '\0';
		else if (i < dstsize)
			dst[i] = src[j];
		if (src[j] == '\0')
			return (i);
		i++;
		j++;
	}
}