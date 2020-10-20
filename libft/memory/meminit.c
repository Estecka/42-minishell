/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meminit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 18:12:20 by abaur             #+#    #+#             */
/*   Updated: 2020/10/17 18:16:48 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

extern void	ft_bzero(void *s, size_t n)
{
	char	*c;
	size_t	i;

	c = s;
	i = 0;
	while (i < n)
		c[i++] = '\0';
}

extern void	*ft_memset(void *b, int c, size_t len)
{
	char	*str;
	size_t	i;

	str = (char*)b;
	i = 0;
	while (i < len)
		str[i++] = (unsigned char)c;
	return (b);
}
