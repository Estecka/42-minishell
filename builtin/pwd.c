/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 10:38:02 by hherin            #+#    #+#             */
/*   Updated: 2020/10/27 14:15:52 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int			pwd_built(int argc, char **args)
{
	char	*buf;

	(void)args;
	(void)argc;
	buf = getcwd(NULL, 0);
	if (!buf)
		buf = ft_strdup(g_pwd_save);
	ft_putstr(buf);
	write(1, "\n", 1);
	free(buf);
	return (errno);
}
