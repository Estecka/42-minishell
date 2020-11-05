/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envclear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 10:16:19 by hherin            #+#    #+#             */
/*   Updated: 2020/11/05 15:27:33 by abaur            ###   ########.fr       */
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

static char			**free_envarray(char **pwd)
{
	if (*pwd)
		free(*pwd);
	free(g_envarray.content);
	g_envarray = (t_dynarray){0};
	return (0);
}

// Many lines can be saved using `set_env_var` instead of dynnapend
extern char			**envnulinit(void)
{
	const char		*var;
	char			*pwd;
	int				size;

	size = 7;
	pwd = NULL;
	if (!dyninit(&g_envarray, sizeof(char**), size, 1))
		return (NULL);
	if (!(var = ft_strdup("LESSCLOSE=/usr/bin/lesspipe %s %s")))
		return (free_envarray(&pwd));
	dynappend(&g_envarray, &var);
	if (!(var = ft_strdup("LESSOPEN=| /usr/bin/lesspipe %s")))
		return (free_envarray(&pwd));
	dynappend(&g_envarray, &var);
	if (!(var = ft_strdup("LS_COLORS")))
		return (free_envarray(&pwd));
	dynappend(&g_envarray, &var);
	if (!(var = ft_strdup("OLDPWD")))
		return (free_envarray(&pwd));
	dynappend(&g_envarray, &var);
	pwd = getcwd(NULL, 0);
	if (!(var = ft_strjoin("PWD=", pwd)))
		return (free_envarray(&pwd));
	dynappend(&g_envarray, &var);
	if (!(var = ft_strdup("SHLVL")))
		return (free_envarray(&pwd));
	dynappend(&g_envarray, &var);
	g_environ = (char***)&g_envarray.content;
	return (char**)(g_envarray.content);
}
