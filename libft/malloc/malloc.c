/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 12:58:52 by abaur             #+#    #+#             */
/*   Updated: 2020/10/17 19:38:29 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_memory.h"

#include <stdlib.h>

extern void			*ft_calloc(size_t count, size_t size)
{
	void	*result;

	size *= count;
	result = malloc(size);
	if (result)
		ft_bzero(result, size);
	return (result);
}

extern void*const	*malloc2d(size_t width, size_t height, size_t type)
{
	char			**result;
	char			*values;
	size_t			i;

	result = malloc(
		(sizeof(void*) * width)
		+ (type * height * width));
	if (!result)
		return (NULL);
	values = (char*)(result + width);
	i = -1;
	while (++i < (width * height * type))
		values[i] = 0;
	i = -1;
	while (++i < width)
		result[i] = values + (i * height * type);
	return ((void**)result);
}
