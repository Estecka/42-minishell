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

typedef struct s_cmdexpr	t_cmdexpr;
typedef enum e_iotype		t_iotype;

/*
** The kind of input/output redirection used by a process.
** @var io_standard	No redirection
** @var io_truncate	(<, >) Input/output from/into a file. 
** @var io_append  	(>>) output only; append to existing file content
** @var io_pipe    	(|) input/output is piped from/to another process.
*/

enum	e_iotype
{
	io_standard = 0,
	io_truncate = 1,
	io_append = 2,
	io_pipe = 3,
};

/*
** The target for an input/output redirection.
** @var char* path	The path to the target file. Applicable only if the io_type
**  is either `io_truncate` or `io_append`.
** @var t_cmdexp* expr	The expression of the process to be piped with. Applica
** ble only if the io_type is `io_pipe`.
*/

union u_iotarget
{
	char		*path;
	t_cmdexpr	*expr;
};

/*
** A breakdown of a single process.
** @var char** args	The arguments passed to the process, this includes the exec
** utable's name.
** @var t_iotype outtype
** @var t_iotype outtype
** @var char*|t_cmdexpr* input	The file or process to read input from.
** @var char*|t_cmdexpr* output	The file or process to write outpur to.
*/

struct	s_cmdexpr
{
	char				**args;
	t_iotype			intype;
	t_iotype			outtype;
	union u_iotarget	input;
	union u_iotarget	output;
};

#endif
