/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 14:50:50 by abaur             #+#    #+#             */
/*   Updated: 2020/11/15 16:45:46 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

extern int	ft_strcmp(const char *s1, const char *s2)
{
	int	diff;

	diff = 0;
	while (!diff)
	{
		diff = (unsigned char)*s1 - (unsigned char)*s2;
		if (!*s1 || !*s2)
			break ;
		s1++;
		s2++;
	}
	return (diff);
}

extern int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int		diff;
	size_t	i;

	i = 0;
	diff = 0;
	while (!diff && i++ < n)
	{
		diff = (unsigned char)*s1 - (unsigned char)*s2;
		if (!*s1 || !*s2)
			break ;
		s1++;
		s2++;
	}
	return (diff);
}

extern int	ft_strccmp(const char *s1, const char *s2, char terminator)
{
	int	diff;

	diff = 0;
	while (1)
	{
		diff = (unsigned char)(*s1 * (*s1 != terminator))
			- (unsigned char)(*s2 * (*s2 != terminator));
		if (diff || (*s1 == terminator) || (*s2 == terminator) || !*s1 || !*s2)
			break ;
		s1++;
		s2++;
	}
	return (diff);
}
