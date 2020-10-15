/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:27:11 by hherin            #+#    #+#             */
/*   Updated: 2020/10/15 11:52:21 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <stdio.h>
#include <string.h>
 
static void	print_error(char **args, int error)
{
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(error), 2);
	write(2, "\n", 1);
}

static int		change_dir(char **args)
{
	char *dir;
	char	*tmp;

	dir = (!args[1] || !args[1][1] || !ft_strncmp(args[1], "~", 1)) ? \
	get_env_var("HOME") : ft_strdup(args[1]);
	tmp = dir;
	dir = ft_strjoin(dir, args[1]);
	free(tmp);
	if (chdir(dir) == -1)
		print_error(args, errno);
	free(dir);
	return (errno);
}


int		cd_built(int argc, char **args)
{
	int		i;
	char	**tmp;
	char	*tmp2;
	char	*tmp3;

	(void)argc;
	i = 0;
	tmp2 = NULL;
	tmp = (char**)(g_envarray.content);
	if (change_dir(args))
		return (errno);
	while (tmp[i])
	{
		if (!ft_strncmp("PWD", tmp[i], 3))
		{
			tmp2 = ((char**)(g_envarray.content))[i];
			tmp3 = getcwd(NULL, 0);
			((char**)(g_envarray.content))[i] = ft_strjoin("PWD=", tmp3);
			free(tmp3);
		}
		i++;
	}
	i = 0;
	while (tmp[i])
	{
		if (!ft_strncmp("OLDPWD", tmp[i], 6))
		{
			free(((char**)(g_envarray.content))[i]);
			((char**)(g_envarray.content))[i] = ft_strjoin("OLDPWD=", tmp2 + 4);
		}
		i++;
	}
	free(tmp2);
	return (errno);
}

/*
** cas //tmp pas gere
** cd et ~ donne une erreur
*/