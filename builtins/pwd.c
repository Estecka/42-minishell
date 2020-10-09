/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 10:38:02 by hherin            #+#    #+#             */
/*   Updated: 2020/10/09 10:59:54 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		pwd_built(char **args)
{
    char	*buf;

	buf = NULL;
	if (ft_strlen(args[0]) != 3)
	{
		ft_putstr(args[0]);
		ft_putstr(": command not found\n");
		return (0);
	}
	buf = getcwd(buf, 0);
	ft_putstr(buf);
	write(1, "\n", 1);
	free(buf);
	return (errno);
}