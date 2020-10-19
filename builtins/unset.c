/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 15:23:50 by hherin            #+#    #+#             */
/*   Updated: 2020/10/19 10:29:42 by hherin           ###   ########.fr       */
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
	ret = malloc(sizeof(char) * i + 1);
	ft_strlcpy(ret, s, i);
	return (ret);
}

static int	get_double_size(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

static int	is_unset(char **args, int argc, char *env)
{
	int i;
	char	*name;

	i = 1;
	name = get_envname(env);
	while (i < argc)
	{
		if (ft_strncmp(args[i], name, ft_strlen(args[i]) + 1))
			return (1);
		i++;
	}
	return (0);
}

int		unset_built(int argc, char **args)
{
	char	**new_env;
	char	**env;
	size_t	i_env;
	size_t	i_new;

	i_env = 0;
	i_new = 0;
	env = ((char**)(g_envarray.content));
	if (!args[1])
		return (0);
	new_env = malloc(sizeof(char*) * (get_double_size(env) + 1));
	while (env[i_env])
	{
		if (is_unset(args, argc, env[i_env]))
		{
			new_env[i_new] = malloc(sizeof(char) * ft_strlen(env[i_env] + 1));
			ft_strlcpy(new_env[i_new], env[i_env], ft_strlen(env[i_env]));
			i_new++;
		}
		i_env++;
	}
	new_env[i_new] = NULL;
	free_mtab(&env);
	g_envarray.content = (void*)new_env;
	return(0);
}