/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 11:36:36 by hherin            #+#    #+#             */
/*   Updated: 2020/10/14 18:05:21 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	print_error(char *args)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(args, 2);
	ft_putstr_fd(": command not found\n", 2);
}

t_builtin			builtins_process(char **args)
{
	if (!ft_strncmp(args[0], "echo", 5))
		return (&echo_built);
	else if (!ft_strncmp(args[0], "pwd", 4))
		return (&pwd_built);
	else if (!ft_strncmp(args[0], "env", 4))
		return (&env_built);
	else if (!ft_strncmp(args[0], "cd", 4))
		return (&cd_built);
	else
		print_error(args[0]);
	return (NULL);
}