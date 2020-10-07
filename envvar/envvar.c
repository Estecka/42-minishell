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

extern void			envvarinit(char **environ)
{
	g_envarray.content = environ;
	g_envarray.type = sizeof(char*);
	g_envarray.nullterm = 1;
	g_envarray.length = 0;
	g_envarray.capacity = g_envarray.length + 1;
	g_environ = (char***)&g_envarray.content;
}


extern char			*get_env_var(const char *name)
{
	(void)name;
	return(0);
}
