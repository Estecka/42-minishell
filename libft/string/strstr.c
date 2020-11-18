/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 15:34:54 by abaur             #+#    #+#             */
/*   Updated: 2020/11/15 16:44:14 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

extern char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*result;
	size_t		i;
	size_t		j;

	if (!*needle)
		return ((char*)haystack);
	i = 0;
	while (haystack[i] && i < len)
	{
		if (*needle == haystack[i])
		{
			j = 0;
			result = &haystack[i];
			while (j + i < len && needle[j] == haystack[j + i])
			{
				if (needle[j + 1] == '\0')
					return ((char*)result);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}
