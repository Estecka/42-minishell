/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envclear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 10:16:19 by hherin            #+#    #+#             */
/*   Updated: 2020/10/19 11:58:00 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envvar.h"
#include "../libft/libft.h"
#include <stdio.h>
static int	is_envvar(char **env, char *delet)
{
	int		i_env;

	i_env = 0;
	while (env[i_env])
	{
		if (!ft_strccmp(env[i_env], delet, '=') || \
			!ft_strccmp(env[i_env], delet, '\0'))
			return (i_env);
		i_env++;
	}
	return (-1);
}

void	envclear(char *delet)
{
	int		curs;
	char 	**env;

	env = (char**)(g_envarray.content);
	curs = is_envvar(env, delet);
	while (env[curs++])
		env[curs - 1] = env[curs]; 
	if (curs > 0)
	{
		env[curs] = NULL;
		g_envarray.length--;
	}
}