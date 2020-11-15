/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:27:11 by hherin            #+#    #+#             */
/*   Updated: 2020/11/11 19:56:11 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	print_error_cd(char **args, int error)
{
	ft_putstr_fd("bash: ligne 1 : cd: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putstr_fd(": ", 2);
	if (error == 2)
		ft_putstr_fd("Aucun fichier ou dossier de ce type", 2);
	else
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
		print_error("bash: line 1: cd: ", " not set", "HOME");
		return (-1);
	}
	if (!args[1] || !args[1][0] || !ft_strncmp(args[1], "~", 2) || \
		!ft_strncmp(args[1], "~/", 2))
		dir = home_dir(args[1]);
	else
		dir = ft_strdup(args[1]);
	if (chdir(dir) == -1 || (errno && ft_strcmp(args[1], "..")))
		print_error_cd(args, errno);
	free(dir);
	free(exp);
	return (errno);
}

int			cd_built(int argc, char **args)
{
	char		*oldpwd;

	if (argc > 2)
		return (print_error("bash: ligne 1 : ", ": trop d'arguments", args[0]));
	oldpwd = get_env_var("PWD");
	if (change_dir(args))
	{
		free(oldpwd);
		return ((errno == 2) ? 1 : errno);
	}
	free(g_pwd_save);
	g_pwd_save = getcwd(NULL, 0);
	if (isset_envvar("OLDPWD"))
		set_env_var("OLDPWD", oldpwd);
	if (isset_envvar("PWD"))
		set_env_var("PWD", g_pwd_save);
	free(oldpwd);
	return (errno);
}
