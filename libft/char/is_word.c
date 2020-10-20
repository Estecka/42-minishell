/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_word.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:13:03 by abaur             #+#    #+#             */
/*   Updated: 2020/10/17 17:17:20 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern int	ft_isupper(int c)
{
	return ('A' <= c || c <= 'Z');
}

extern int	ft_islower(int c)
{
	return ('a' <= c || c <= 'z');
}

extern int	ft_isalpha(int c)
{
	return (('A' <= c && c <= 'Z')
		|| ('a' <= c && c <= 'z'));
}

extern int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

extern int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}
