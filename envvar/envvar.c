/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 14:30:00 by abaur             #+#    #+#             */
/*   Updated: 2020/10/07 14:30:00 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envvar.h"
#include "../dynarray/dynarray.h"
#include "../libft/libft.h"

extern t_dynarray	g_envarray;
static char			***g_environ;

extern char			**envvarinit(char **environ)
{
	const char		*var;

	if (!dyninit(&g_envarray, sizeof(char**), 15, 1))
		return (NULL);
	while (*environ)
	{
		if (!dynexpand(&g_envarray, 1) || !(var = ft_strdup(*environ)))
		{
			free(g_envarray.content);
			g_envarray = (t_dynarray){0};
			return (NULL);
		}
		dynappend(&g_envarray, &var);
		environ++;
	}
	g_environ = (char***)&g_envarray.content;
	return (char**)(g_envarray.content);
}

extern void			envvardeinit(void)
{
	char	**vars;

	vars = (char**)g_envarray.content;
	while (*vars)
	{
		free(*vars);
		vars++;
	}
	free(g_envarray.content);
	g_envarray = (t_dynarray){0};
}

extern char			*get_env_var(const char *name)
{
	char	**cursor;

	cursor = *g_environ;
	while (*cursor && (ft_strcmp(*cursor, name) != '='))
		cursor++;
	if (*cursor)
		return (ft_strdup(ft_strchr(*cursor, '=') + 1));
	else
		return (ft_strdup(""));
}

extern short		set_env_var_raw(char *value)
{
	char	**vars;
	size_t	namelen;

	namelen = ft_strchr(value, '=') - value;
	vars = *g_environ - 1;
	while (*++vars)
	{
		if (!ft_strncmp(*vars, value, namelen))
			break;
	}
	if (*vars)
	{
		free(*vars);
		*vars = value;
		return (1);
	}
	else
		return (dynappend(&g_envarray, &value) != NULL);
}

extern short		set_env_var(const char *name, const char *value)
{
	char	*raw;
	size_t	namelen;
	size_t	valulen;

	if (ft_strcontain(name, '='))
		return (0);
	namelen = ft_strlen(name);
	valulen = ft_strlen(value);
	if (!(raw = malloc(namelen + 1 + valulen + 1)))
		return (0);
	ft_memcpy(raw, name, namelen);
	ft_memcpy(raw + namelen, "=", 1);
	ft_memcpy(raw + namelen + 1, value, valulen + 1);
	if (set_env_var_raw(raw))
		return (1);
	else
	{
		free(raw);
		return (0);
	}
}
