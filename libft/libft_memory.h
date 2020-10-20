/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_memory.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:32:47 by abaur             #+#    #+#             */
/*   Updated: 2020/10/17 18:05:20 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MEMORY_H
# define LIBFT_MEMORY_H

# include <stdlib.h>

/*
** Overwite the given memory space with 0's.
** @param void* dst	The memory to overwrite.
** @param size_t size	The amount of bytes to write.
*/

void	ft_bzero(void *dst, size_t size);

/*
** Overwrite a memory space withe the given bytes.
** @param void* dst	The memory to overwrite.
** @param int value	The value to write each byte with.
** @param size_t size	The amount of bytes to write.
** @return void*	`dst`
*/

void	*ft_memset(void *dst, int value, size_t size);

/*
** Copies data into another memory space.
** Behaviour is undefined if the two memories overlap.
** @param void* dst	The memory to overwrite.
** 	This can safely be passed NULL
** @param const void* src	The values to write with.
** 	This can safely be passed NULL.
** @param size_t size	The amount of bytes to write.
** @return void*
** 	`dst`	Success
** 	NULL	Either dst or src is NULL.
*/

void	*ft_memcpy(void *dst, const void *src, size_t size);

/*
** Copies data into another memory space, until a given byte is found.
** The terminating byte is also copied.
** Behaviour is undefined if the two memories overlap.
** @param void* dst	The memory to overwrite.
** @param const void* src	The values to write with.
** @param size_t size	The maximum amount of bytes to write.
** @return void* If a byte of the given value was found, returns the adress of 
**  the next byte in dst. Otherwise, returns NULL.
*/

void	*ft_memccpy(void *dst, const void *src, int value, size_t size);

/*
** Copies `len` bytes from `src` to `dst`.
** The memory areas may overlap, in which case dst will overwrite src.
*/
/*
** Displaces memory.
** The source and destination may safely overlap, in which case the source may
**  may be modified.
** @param void* dst	The memory to overwrite
** @param const void* src	The values to write with.
** @param size_t size	The amount of bytes to write.
** @return void*	`dst`
*/

void	*ft_memmove(void *dst, const void *src, size_t size);

/*
** Locates the first byte with the given value?
** @param const void* src	The memory to search.
** @param int value	The value of the byte to look for.
** @param size_t size	The amount of bytes to search.
** @return void*	The adress of the byte if found, NULL otherwise.
*/

void	*ft_memchr(const void *src, int value, size_t size);

/*
** Compare the values in two memory spaces.
** @param const void* m1	The first memory to compare.
** @param const void* m2	The other memory to compare.
** @param size_t size	The maximum amount of bytes to compare.
** @return int	If the memories differ, returns the difference between their fi
** rst different bytes. 0 otherwise.
*/

int		ft_memcmp(const void *m1, const void *m2, size_t size);

#endif
