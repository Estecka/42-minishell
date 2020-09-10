/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:38:42 by abaur             #+#    #+#             */
/*   Updated: 2020/01/28 16:12:34 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/*
** A breakdown of a single process.
** @var char** args	The arguments passed to the process, this includes the exec
** utable's name.
** t_procexpr* pipein	The process expression that pipes into this.
** t_procexpr* pipeout	The process expression this pipes into.
** @var char** inputs	An array of pathes to the input files.
** 	This array is null-terminated.
** @var char** outputs	An array of pathes to the output files.
** 	This array is null-terminated.
** @var short* outtypes	For each output, whether this redirection is truncate (
** TRUE) or append (FALSE).
** 	This array is not NULL-terminated, but has the same length as `outputs` (mi
** nus the null terminator);
*/

typedef struct s_procexpr	t_procexpr;
struct		s_procexpr
{
	char		**args;

	t_procexpr	*pipein;
	t_procexpr	*pipeout;

	char		**inputs;
	char		**outputs;
	short		*outtypes;
};

/*
** Parses all commands in the given line.
** @param char* line	The full line that contains the commands.
** @return t_procexpr*	An array of command expressions.
*/

t_procexpr	**get_next_cmdline(const char *line);

/*
** Recursively frees a process expression, all of its components and chained pr
** ocesses.
** @param t_procexpr* expr	The expression to destroy.
*/

void		procexpr_destroy(t_procexpr *expr);

#endif
