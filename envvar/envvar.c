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

static t_dynarray	g_envarray = {0};
static char			***g_environ;

extern char			**envvarinit(char **environ)
{
	const char		*var;

	if (!dyninit(&g_envarray, sizeof(char**), 15, 1))
		return (NULL);
	while(*environ)
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
