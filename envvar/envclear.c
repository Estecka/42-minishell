/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envclear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 10:16:19 by hherin            #+#    #+#             */
/*   Updated: 2020/11/05 16:13:39 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envvar.h"
#include "../libft/libft.h"
#include "../builtin/builtins.h"

extern t_dynarray	g_envarray;

static int			is_envvar(char **env, char *delet)
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

extern int			envclear(char *delet)
{
	int		curs;
	char	**env;

	env = (char**)(g_envarray.content);
	if ((curs = is_envvar(env, delet)) == -1)
		return (0);
	if (!ft_strncmp("HOME", delet, 5) && !g_home_save)
		g_home_save = ft_strdup(env[curs]);
	if (!ft_strncmp("PWD", delet, 4) && !g_pwd_save)
		g_pwd_save = ft_strdup(env[curs]);
	free(env[curs]);
	while (env[curs++])
		env[curs - 1] = env[curs];
	env[curs] = NULL;
	g_envarray.length--;
	return (1);
}

extern char			**envnulinit(void)
{
	char	*pwd;

	if (!dyninit(&g_envarray, sizeof(char**), 7, 1))
		return (NULL);
	pwd = getcwd(NULL, 0);
	g_environ = (char***)&g_envarray.content;
	if (!set_env_var("LESSCLOSE", "/usr/bin/lesspipe %s %s")
		|| !set_env_var("LESSOPEN", "| /usr/bin/lesspipe %s")
		|| !set_env_var("LSCOLORS", "")
		|| !set_env_var("OLDPWD", "")
		|| !set_env_var("SHLVL", "")
		|| !set_env_var("PWD", pwd))
	{
		free(g_envarray.content);
		g_envarray = (t_dynarray){0};
	}
	free(pwd);
	return (*g_environ);
}
