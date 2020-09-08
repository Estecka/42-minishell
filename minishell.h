/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:38:42 by abaur             #+#    #+#             */
/*   Updated: 2020/01/28 16:12:34 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_procexpr	t_procexpr;

/*
** A breakdown of a single process.
** @var char** args	The arguments passed to the process, this includes the exec
** utable's name.
** t_procexpr* pipein	The process expression that pipes into this.
** t_procexpr* pipeout	The process expression this pipes into.
** @var char** inputs	The pathes to the input files.
** 	This array will be null-terminated.
** @var char** outputs	The pathes to the output files.
** 	This array will be null-terminated.
** @var short* outtypes	For each output, whether this redirection is truncate (
** TRUE) or append (FALSE).
** 	This array is not NULL-terminated, but has the same length as `outputs`;
*/

struct	s_procexpr
{
	char		**args;

	t_procexpr	*pipein;
	t_procexpr	*pipeout;

	char		**inputs;
	char		**outputs;
	short		*outtypes;
};

#endif
