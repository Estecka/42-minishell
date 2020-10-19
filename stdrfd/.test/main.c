/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 13:59:54 by abaur             #+#    #+#             */
/*   Updated: 2020/10/19 15:27:08 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../stdrfd.h"

#include "../../get_next_line/get_next_line.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char* locate_file(const char* line)
{
	while (*line && *line != '>')
		line++;
	while (*line == '>')
		line++;
	return (char*)line;
}

extern int main()
{
	char* line;

	if (!backup_stdrfd())
	{
		dprintf(2, "Fd backup failed: [%s]\n", strerror(errno));
		return (-1);
	}
	dprintf(2, "New FD's are : %d %d\n", g_stdrfd[0], g_stdrfd[1]);

	while(get_next_line(0, &line) > 0)
	{
		int		fd = -1;
		char*	filepath = locate_file(line);

		if (*filepath)
		{
			fd = open(filepath, 
				O_RDWR | O_CREAT | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH
				);
			if (fd < 0)
			{
				dprintf(2, "Could not open file : [%s] \"%s\"\n", strerror(errno), filepath);
				free(line);
				continue;
			}
			if (dup2(fd, 0) < 0)
			{
				dprintf(2, "Couldn't duplicate fd %d: [%s]\n", fd, strerror(errno));
			}
			close(fd);
		}
		dprintf(0, "Argument is: \"%.*s\"\n", (int)(filepath - line), line);
		if (*filepath && !restore_stdrfd())
			dprintf(2, "Fd restore failed: [%s]\n", strerror(errno));
		free(line);
	}

	if (line)
		free(line);
}