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
typedef struct s_ioredir	t_ioredir;
typedef enum e_iotype		t_iotype;
typedef union u_iotarget	t_iotarget;

/*
** The kind of input/output redirection used by a process.
** @var io_standard	Using stdin/stdout.
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

union	u_iotarget
{
	char		*path;
	t_cmdexpr	*expr;
};

/*
** Represents an input/output redirection.
** @var t_iotype type	The type of redirection.
** @var t_iotarget target	The target of the redirection.
*/

struct s_ioredir
{
	enum e_iotype		type;
	union u_iotarget	target;
};


/*
** A breakdown of a single process.
** @var char** args	The arguments passed to the process, this includes the exec
** utable's name.
** @var t_ioredir* inputs	The input sources from first to last.
** 	This array will be null-terminated.
** @var t_ioredir* outputs	The output destinations.
** 	ŧHis array will be null-terminated.
*/

struct	s_cmdexpr
{
	char		**args;
	t_ioredir	*inputs;
	t_ioredir	*outputs;
};

#endif
