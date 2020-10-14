/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 11:36:36 by hherin            #+#    #+#             */
/*   Updated: 2020/10/14 14:21:54 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	print_error(char *args)
{
	ft_putstr(args);
	ft_putstr(": command not found\n");
}

int			*builtins_process(char **args)
{
	if (!ft_strncmp(args[0], "echo", 5))
		return (echo_built(args));
	else if (!ft_strncmp(args[0], "pwd", 4))
		return (pwd_built(args));
	else if (!ft_strncmp(args[0], "env", 4))
		return (env_built(args));
	else
		print_error(args[0]);
	return (NULL);
}