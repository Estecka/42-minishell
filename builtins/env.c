/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 11:19:10 by hherin            #+#    #+#             */
/*   Updated: 2020/10/16 12:07:35 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		env_built(int argc, char **args)
{
	int		i;
	char	**tmp;

	i = 0;
	(void)argc;
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