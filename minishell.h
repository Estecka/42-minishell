/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:41:00 by abaur             #+#    #+#             */
/*   Updated: 2020/11/04 20:49:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parser/parser.h"

char	g_prev_status;

/*
** Prepares the standard fds redirection.
** This will DEFINITELY affect stdin and stdout !! 
** Don't forget to use `restore_stdrfd` to undo these changes !
** @param t_procexpr* proc	The process expression that contains the redirectio
** ns.
** @return int	A status code.
** 	0 in case of success, an errno value otherwise.
** 	errno will not be not be set in case of error.
*/

int		bootstrap_fds(t_procexpr *proc);

int		exec_cmd(int argc, char **argv);
int		execute_cmds_all(t_procexpr **cmdarray);

int    signal_exec(void);

int		clean_exit(int status);

#endif