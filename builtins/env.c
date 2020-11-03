/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 11:19:10 by hherin            #+#    #+#             */
/*   Updated: 2020/11/03 12:11:51 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	*get_envname(char *s)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (s[i] && s[i] != '=')
		i++;
	if (s[i] == '=')
	{
		ret = malloc(sizeof(char) * i + 1);
		ft_strlcpy(ret, s, i);
	}
	return (ret);
}

int			env_built(int argc, char **args)
{
	int		i;
	char	**env;
	char	*value;
	char	*name;

	i = 0;
	env = ((char**)(g_envarray.content));
	(void)args;
	if (argc == 1)
	{
		while (env[i])
		{
			name = get_envname(env[i]);
			value = (name) ? get_env_var(name) : NULL;
			if (value)
			{
				ft_putstr(env[i]);
				write(1, "\n", 1);
			}
			free(name);
			free(value);
			i++;
		}
	}
	return (errno);
}
