/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 10:38:02 by hherin            #+#    #+#             */
/*   Updated: 2020/10/22 13:21:12 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int			pwd_built(int argc, char **args)
{
	char	*buf;

	(void)args;
	(void)argc;
	buf = getcwd(NULL, 0);
	ft_putstr(buf);
	write(1, "\n", 1);
	free(buf);
	return (errno);
}
