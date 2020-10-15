/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 14:26:00 by abaur             #+#    #+#             */
/*   Updated: 2020/10/15 14:26:00 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
