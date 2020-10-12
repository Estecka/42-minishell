/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 10:53:41 by hherin            #+#    #+#             */
/*   Updated: 2020/10/09 11:09:11 by hherin           ###   ########.fr       */
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

int		 echo_built(char **args)
{
	size_t	i;
	size_t  size;
	size_t  nl_bool;
	size_t  wd_bool;
		
	size = 0;
	while (args[++size])
	{}
	i = 0;
	nl_bool = 1;
	wd_bool = 0;
	while (++i < size && size > 1)
	{
		if (!ft_strncmp(args[i], "-n", 2) && !wd_bool)
			(echo_isnl(args[i], i, size)) ? nl_bool = 0 : 0;
		else
		{
			wd_bool = 1;
			ft_putstr(args[i]);
			(i < size - 1) ? write(1, " ", 1) : 0;
		}
	}
	(nl_bool) ? write(1, "\n", 1) : 0;
	return (errno);
}