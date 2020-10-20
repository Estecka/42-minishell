/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 19:38:33 by abaur             #+#    #+#             */
/*   Updated: 2020/10/17 19:38:57 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

extern void	freearray(void **array)
{
	array--;
	while (*++array)
		free(*array);
}

extern void	freearrayn(void **array, size_t size)
{
	array--;
	while (size--)
		if (*++array)
			free(*array);
}
