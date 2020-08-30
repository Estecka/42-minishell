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
** The kind of input/output redirection used by a process.
** @value standard	stdin/stdout is used
** @value append	input or output from or into a file.
** @value truncate	output into a file, and replace the content. Not applicable
**  to input.
** @value pipe	input/output is piped from/to another process.
*/

typedef enum e_iotype		t_iotype;
enum	e_iotype
{
	standard = 0,
	append = 1,
	truncate = 2,
	pipe = 3,
};

/*
** A breakdown of a single process.
** @var char** args	The arguments passed to the process, this includes the
** executable's name.
** @var t_iotype outtype
** @var t_iotype outtype
** @var char*|t_cmdexpr* input	The file or process to read input from.
** @var char*|t_cmdexpr* output	The file or process to write outpur to.
**  if any.
** @var t_cmdexpr* pipe	A pointer to a piped process
*/

typedef struct s_cmdexpr	t_cmdexpr;
struct	s_cmdexpr
{
	char const	**args;
	t_iotype	intype;
	t_iotype	outtype;
	void		*input;
	void		*output;
};

#endif
