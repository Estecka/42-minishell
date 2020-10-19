/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdrfd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 13:47:05 by abaur             #+#    #+#             */
/*   Updated: 2020/10/19 14:22:00 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static int		g_stdrfd[3] = {0, 0, 0};

extern short	backup_stdrfd(void)
{
	int i;
	int fd;

	if ((g_stdrfd[0] | g_stdrfd[1] | g_stdrfd[2]) != 0)
		return (0);
	i = -1;
	while (++i < 3)
	{
		fd = dup(i);
		if (fd < 0)
		{
			g_stdrfd[0] = 0;
			g_stdrfd[1] = 0;
			g_stdrfd[2] = 0;
			return (0);
		}
		else
			g_stdrfd[i] = fd;
	}
	return (1);
}

extern short	restore_stdrfd(void)
{
	int		i;
	short	status;

	if ((g_stdrfd[0] & g_stdrfd[1] & g_stdrfd[2]) == 0)
		return (0);
	status = 1;
	i = -1;
	while (++i < 3)
	{
		if ((close(i) < 0) || (dup2(g_stdrfd[i], i) < 0))
			status = 0;
	}
	return (status);
}
