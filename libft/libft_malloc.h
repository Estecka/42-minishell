/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_malloc.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 19:17:09 by abaur             #+#    #+#             */
/*   Updated: 2020/10/17 19:30:49 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

# include <stdlib.h>

/*
** Allocates an array of objects.
** The array will be initialized with zero's.
** @param size_t count	The amount of elements in the array.
** 	This should include the null terminator if one is needed.
** @param size_t type	The size of a single element.
** @return void* The allocated memory, or NULL if it failed.
*/

void		*ft_calloc(size_t count, size_t type);

/*
** Allocates a two dimensional array in a single memory space.
** The array's elements are accessible via `array[x][y]`.
** The array's elements are initialized with zero's;
** @param size_t width	The number of columns. (x)
** @param size_t height	The number of rows.    (y)
** @param size_t type	The size of a single element. (sizeof(type))
** @return void*const*	The allocated memory, or NULL if it failed.
*/

void*const	*malloc2d(size_t width, size_t height, size_t type);


/*
** Frees all pointers in a null-terminated array.
** This does NOT free the array itself.
** @param void** array	A pointer to the array.
*/

void		freearray(void **array);

/*
** Frees n consecutive pointers in an array.
** This does NOT free the array itself.
** This will NOT stop at any null-terminator, but safely ignores them.
** @param void** array	A pointer to the array.
** @param size_t size	The amount of elements to browse through.
*/

void		freearrayn(void **array, size_t size);

#endif