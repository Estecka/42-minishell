/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bootstrap_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 14:17:25 by abaur             #+#    #+#             */
/*   Updated: 2020/11/09 16:27:07 by abaur            ###   ########.fr       */
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
	return (0);
}

static int	bootstrap_fds2(char *path, t_punctuation mode)
{
	int fd;
	int status;

	if (mode == punc_input)
		fd = open(path, O_RDONLY);
	else
		fd = open(path,
			O_RDWR | O_CREAT | (mode == punc_truncate ? O_TRUNC : O_APPEND),
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (fd < 0)
		return (0 & err_msg(path, errno));
	status = dup2(fd, mode == punc_input ? 0 : 1);
	close(fd);
	if (status < 0)
		return (0 & err_msg("Redirection hook", errno));
	return (1);
}

extern int	bootstrap_fds(t_procexpr *proc)
{
	int i;

	i = -1;
	while (proc->ioarray[++i])
		if (!bootstrap_fds2(proc->ioarray[i], proc->iotypes[i]))
			return (-1);
	return (0);
}
