/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:27:11 by hherin            #+#    #+#             */
/*   Updated: 2020/10/22 13:14:02 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	print_error_cd(char **args, int error)
{
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(error), 2);
	write(2, "\n", 1);
}

static int	change_dir(char **args)
{
	char		*dir;
	char		*exp;

	exp = get_env_var("HOME");
	if ((!args[1] || (args[1] && !*args[1])) && !(*exp))
	{
		free(exp);
		print_error("bash: cd: ", " not set", "HOME");
		return (errno);
	}
	if (!args[1] || !args[1][0] || !ft_strncmp(args[1], "~", 2) || \
		!ft_strncmp(args[1], "~/", 2))
		dir = home_dir(args[1]);
	else
		dir = ft_strdup(args[1]);
	if (chdir(dir) == -1)
		print_error_cd(args, errno);
	if (g_pwd_save)
	{
		free(g_pwd_save);
		g_pwd_save = ft_strdup(dir);
	}
	free(dir);
	free(exp);
	return (errno);
}

/*
** static char		*set_oldpwd(char *args)
** {
** 	int			retro;
**
** 	retro = 0;
** 	(!ft_strncmp(args[1], "./", 0)) ? args[1] += 2 : 0;
** 	while (!ft_strncmp(args[1], "./", 0))
** }
*/

/*
** TODO: Peux probablement économiser des lignes en utilisant la fonction
** `set_env_var(const char *name, const char *value)`
*/

static void	update_envvar(void)
{
	int		i;
	char	**tmp;
	char	*tmp2;
	char	*tmp3;

	i = 0;
	tmp2 = NULL;
	tmp = (char**)(g_envarray.content);
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
			((char**)(g_envarray.content))[i] = (!g_pwd_save) ? \
				ft_strjoin("OLDPWD=", tmp2 + 4) : 0; // : set_oldpwd();
		}
		i++;
	}
	free(tmp2);
}

/*
** mettre a null quand on export HOME et PWD
*/

int			cd_built(int argc, char **args)
{
	(void)argc;
	if (change_dir(args))
		return (errno);
	(!g_pwd_save) ? update_envvar() : 0;
	return (errno);
}
