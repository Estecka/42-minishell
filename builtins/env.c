/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 11:19:10 by hherin            #+#    #+#             */
/*   Updated: 2020/10/14 16:31:00 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <stdio.h>
int		env_built(char **args)
{
	int i = 0;
	char	**tmp;

	tmp = ((char**)(g_envarray.content));
	(void)args;
	while (tmp[i])
	{
		ft_putstr(tmp[i]);
		write(1, "\n", 1);
		i++;
	}
	return (errno);
}