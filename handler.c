/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 15:23:26 by abaur             #+#    #+#             */
/*   Updated: 2020/11/18 19:07:17 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft/libft.h"
#include "minishell.h"
#include <stdio.h>

extern short	g_prompt;

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		(!g_prompt) ? write(0, "> ", 2) : 0;
	}
	if (sig == SIGQUIT)
	{
		if (!g_prompt)
		{
			ft_putstr_fd("\b \b", 1);
			ft_putstr_fd("\b \b", 1);
		}
		else
			write(2, "Exit (core dumped)\n", 19);
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
