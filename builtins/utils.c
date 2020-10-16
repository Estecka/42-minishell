/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 16:46:03 by hherin            #+#    #+#             */
/*   Updated: 2020/10/16 14:45:54 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char		*home_dir(char *args)
{
	char	*tmp;
	char	*add_slash;
	char	*dir;
	int		curs;

	tmp = get_env_var("HOME");
	add_slash = ft_strjoin(tmp, "/");
	curs = (args) ? 2 : 0;
	dir = ft_strjoin(add_slash, args + curs);
	free(tmp);
	free(add_slash);
	return (dir);
}

void		free_mtab(char ***tab)
{
	int		i;

	i = 0;
	while ((*tab)[i])
	{
		free((*tab)[i]);
		i++;
	}
	free((*tab));
}

int	print_error(char *s1, char *s2, char *args)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(args, 2);
	ft_putstr_fd(s2, 2);
	return (1);
}

long long			ft_atoi_ll(const char *str)
{
	short			sign;
	long long		result;
	int				digit;

	while (ft_strcontain("\t\n\r\v\f ", *str))
		str++;
	sign = 1;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign *= -1;
	result = 0;
	while (*str)
	{
		digit = indexof(*str, "0123456789");
		if (digit < 0)
			return (result);
		result *= 10;
		result += digit * sign;
		str++;
	}
	return (result);
}