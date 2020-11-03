/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:32:49 by heleneherin       #+#    #+#             */
/*   Updated: 2020/11/03 17:49:59 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envvar.h"
#include <stdio.h>

void	shell_level(void)
{
	char **env;
	// int		level;
	// char	*

	env = (char**)(g_envarray.content);

	printf("var %s\n", get_env_var("SHLVL"));
}