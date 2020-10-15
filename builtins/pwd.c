/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 10:38:02 by hherin            #+#    #+#             */
/*   Updated: 2020/10/15 11:53:27 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		pwd_built(int argc, char **args)
{
    char	*buf;

	buf = NULL;
	(void)args;
	(void)argc;
	buf = getcwd(buf, 0);
	ft_putstr(buf);
	write(1, "\n", 1);
	free(buf);
	return (errno);
}