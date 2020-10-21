/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 12:05:31 by hherin            #+#    #+#             */
/*   Updated: 2020/10/21 15:55:43 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern char	g_prev_status;

static int	is_str_digit(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
		{
			if (i == 0 && s[0] == '-')
				break;
			else
			{
				print_error("minishell: exit: ", ": numeric argument required\n", s);
				exit(255);
			}
		}
		i++;
	}
	return (1);
}

int		exit_built(int argc, char **args)
{
	long long	nb;
	
	if (argc > 1)
	{
		is_str_digit(args[1]);
		nb = ft_atoi_ll(args[1]);
		if ((ft_strlen(args[1]) > 19 && ft_isdigit(args[1][0])) ||
			(ft_strlen(args[1]) > 20 && args[1][0] == '-'))
		{
			write(1, "exit\n", 5);
			print_error("minishell: exit: ", ": numeric argument required\n", args[0]);
			exit(255);
		}
		if ((args[1][0] == '-' && nb > 0) ||
			(ft_isdigit(args[1][0]) && nb < 0))
		{
			write(1, "exit\n", 5);
			print_error("minishell: exit: ", ": numeric argument required\n", args[0]);
			exit(255);
		}
	}
	write(1, "exit\n", 5);
	exit(EXIT_SUCCESS);
}