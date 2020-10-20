/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bootstrap_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 14:17:25 by abaur             #+#    #+#             */
/*   Updated: 2020/10/20 14:53:01 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "parser/parser.h"
#include "stdrfd/stdrfd.h"

#include <errno.h>
#include <fcntl.h>
#include <string.h>

static int	bootstraps_inputs(t_procexpr *proc)
{
	int i;
	int fd;
	int status;

	errno = 0;
	i = -1;
	if (proc->inputs[++i])
	{
		status = open(proc->inputs[i], O_RDONLY);
		if (status < 0)
			goto endif;
		fd = status;
		status = dup2(fd, 0);
		if (status < 0)
			goto endif;
		close(fd);
	}
	endif:
	status = errno;
	errno = 0;
	return (status);
}

int	bootstraps_outputs(t_procexpr *proc)
{
	(void)proc;
	return (-1);
}

extern int	bootstrap_fds(t_procexpr *proc)
{
	int status;

	status = 0;
	if (bootstraps_inputs(proc) /*|| bootstraps_outputs(proc)*/)
	{
		ft_putstr_fd("Failed to bootstraps fds : ", 2);
		ft_putstr_fd(strerror(errno), 2);
	}
	return (status);
}
