/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdrfd.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 14:04:50 by abaur             #+#    #+#             */
/*   Updated: 2020/10/19 15:44:37 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STDRFD_H
# define STDRFD_H

/*
** Makes a backup of the current standard fd's (stdin, stdout, stderr).
** This will fail with no errno if a backup already exists.
** @return bool
** 	true 	OK
** 	false	error
*/

short	backup_stdrfd(void);

/*
** Restores the standard fd's to their original files.
** This will fail with no errno if no backups are detected.
** @return bool
** 	true 	OK
** 	false	error
*/

short	restore_stdrfd(void);

#endif
