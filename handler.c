/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 15:23:26 by abaur             #+#    #+#             */
/*   Updated: 2020/11/05 15:23:27 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft/libft.h"
#include "minishell.h"
#include <stdio.h>

void	sig_handler(int sig)
{
	if (sig == SIGINT)
		ft_putstr_fd("\n", 2);
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("\b \b", 1);
		ft_putstr_fd("\b \b", 1);
	}
}

int		signal_exec(void)
{
	if (signal(SIGINT, &sig_handler) == SIG_ERR)
		return (0);
	if (signal(SIGQUIT, &sig_handler) == SIG_ERR)
		return (0);
	return (1);
}
