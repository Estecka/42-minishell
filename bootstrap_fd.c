/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bootstrap_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 14:17:25 by abaur             #+#    #+#             */
/*   Updated: 2020/11/05 14:58:12 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "parser/parser.h"
#include "stdrfd/stdrfd.h"

#include <errno.h>
#include <fcntl.h>
#include <string.h>

static int	err_msg(char *context, int err)
{
	ft_putstr_fd(context, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(err), 2);
	return (-1);
}

static int	bootstraps_inputs(t_procexpr *proc)
{
	int i;
	int fd;
	int status;

	i = -1;
	while (proc->inputs[++i])
	{
		fd = open(proc->inputs[i], O_RDONLY);
		if (fd < 0)
			return (err_msg(proc->inputs[i], errno));
		status = dup2(fd, 0);
		close(fd);
		if (status < 0)
			return (err_msg("STDIN hook", errno));
	}
	return (0);
}

static int	bootstraps_outputs(t_procexpr *proc)
{
	int i;
	int fd;
	int status;

	i = -1;
	while (proc->outputs[++i])
	{
		fd = open(proc->outputs[i],
			O_RDWR | O_CREAT | (proc->outtypes[i] ? O_TRUNC : O_APPEND),
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		if (fd < 0)
			return (err_msg(proc->outputs[i], errno));
		status = dup2(fd, 1);
		close(fd);
		if (status < 0)
			return (err_msg("STDOUT hook", errno));
	}
	return (0);
}

extern int	bootstrap_fds(t_procexpr *proc)
{
	if (bootstraps_inputs(proc) || bootstraps_outputs(proc))
		return (-1);
	else
		return (0);
}
