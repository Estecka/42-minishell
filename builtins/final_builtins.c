/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 11:36:36 by hherin            #+#    #+#             */
/*   Updated: 2020/10/09 12:06:36 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	print_error(char *args)
{
	ft_putstr(args);
	ft_putstr(": command not found\n");
}

int			builtins_process(char **args, char **environ)
{
	if (!ft_strncmp(args[0], "echo", 4) && ft_strlen(args[0]) == 4)
	{	
		if (echo_built(args))
		{
			printf("ERRNO RETURN IN ECHO\n");
			exit(EXIT_FAILURE);
		}
	}	
	else if (!ft_strncmp(args[0], "pwd", 3) && ft_strlen(args[0]) == 3)
	{
		if (pwd_built(args))
		{
			printf("ERRNO RETURN IN PWD\n");
			exit(EXIT_FAILURE);
		}
	}
	else if (!ft_strncmp(args[0], "env", 3) && ft_strlen(args[0]) == 3)
	{
		if (env_built(args, environ))
		{
			printf("ERRNO RETURN IN ENV\n");
			exit(EXIT_FAILURE);
		}
	}
	else
		print_error(args[0]);
	return (0);
}