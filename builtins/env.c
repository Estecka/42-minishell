/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 11:19:10 by hherin            #+#    #+#             */
/*   Updated: 2020/10/14 14:19:33 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		env_built(char **args)
{
	int i = 0;
	(void)args;
	while (((char*)(g_envarray.content))[i])
	{	
		ft_putstr(((char*)(g_envarray.content))[i++]);
		write(1, "\n", 1);	
	}
	return (errno);
}