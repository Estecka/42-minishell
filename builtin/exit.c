 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 12:05:31 by hherin            #+#    #+#             */
/*   Updated: 2020/11/02 12:02:13 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtins.h"

extern char	g_prev_status;

static int	is_str_digit(char *s)
{
	int		i;

	i = -1;
	while (s[++i])
	{
		if (!ft_isdigit(s[i]))
		{
			if (i == 0 && (s[i] == '-' || s[i] == '+'))
				continue;
			else
			{
				print_error("bash: line 1: exit: ",
					": numeric argument required", s);
				exit(255);
			}
		}
	}
	return (1);
}

static void	num_arg(char **args, long long nb)
{
	if ((ft_strlen(args[1]) > 19 && ft_isdigit(args[1][0])) ||
	(ft_strlen(args[1]) > 20 && args[1][0] == '-'))
	{
		print_error("bash: line 1: exit: ", ": numeric argument required", args[1]);
		nb = 255;
		clean_exit(nb);
	}
	else if ((args[1][0] == '-' && nb > 0) ||
	(ft_isdigit(args[1][0]) && nb < 0))
	{
		print_error("bash: line 1: exit: ", ": numeric argument required", args[1]);
		nb = 255;
		clean_exit(nb);
	}
}

int			exit_built(int argc, char **args)
{
	long long	nb;

	nb = g_prev_status;
	if (argc == 1)
		clean_exit(nb);
	else
	{
		is_str_digit(args[1]);
		nb = ft_atoi_ll(args[1]);
		num_arg(args, nb);
	}
	if (argc > 2)
		return (1 && print_error("bash: line 1: ", ": too many arguments", args[0]));
	return (nb);
}