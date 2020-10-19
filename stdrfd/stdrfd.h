/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdrfd.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 14:04:50 by abaur             #+#    #+#             */
/*   Updated: 2020/10/19 15:10:17 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STDRFD_H
# define STDRFD_H

int		g_stdrfd[2];

/*
** Makes a backup of the current standard fd's (stdin, stdout, stderr).
** This will fail if a backup already exists.
** @return bool
** 	true 	OK
** 	false	error
*/

short	backup_stdrfd(void);

/*
** Restores the standard fd's to their original files.
** @return bool
** 	true 	OK
** 	false	error
*/

short	restore_stdrfd(void);

#endif