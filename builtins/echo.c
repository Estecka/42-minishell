/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 10:53:41 by hherin            #+#    #+#             */
/*   Updated: 2020/10/22 13:22:01 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	echo_isnl(char *opt, int i, int size)
{
	int j;

	j = 1;
	while (opt[j])
	{
		if (opt[j] == 'n')
			j++;
		else
		{
			ft_putstr(opt);
			(i < size - 1) ? write(1, " ", 1) : 0;
			return (0);
		}
	}
	return (1);
}

int	echo_built(int argc, char **args)
{
	int		i;
	size_t	nl_bool;
	size_t	wd_bool;

	i = 0;
	nl_bool = 1;
	wd_bool = 0;
	while (++i < argc && argc > 1)
	{
		if (!ft_strncmp(args[i], "-n", 2) && !wd_bool)
			(echo_isnl(args[i], i, argc)) ? nl_bool = 0 : 0;
		else
		{
			wd_bool = 1;
			ft_putstr(args[i]);
			(i < argc - 1) ? write(1, " ", 1) : 0;
		}
	}
	(nl_bool) ? write(1, "\n", 1) : 0;
	return (errno);
}
