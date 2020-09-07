/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internals.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 15:28:00 by abaur             #+#    #+#             */
/*   Updated: 2020/09/01 15:28:00 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INTERNALS_H
# define PARSER_INTERNALS_H

# include "parser.h"
# include "../libft/libft.h"
# include "../dynarray/dynarray.h"

/*
** Environnement for parsing a single command. (';' separated)
** @var const char* cursor	The parser's current position within the command li
** ne.
**
** @var t_cmdexpr* firstproc  	The first process in the command.
** 	This acts as the "return value" of the builder.
** @var t_cmdexpr* currentproc	The process being currently parsed.
**
** @var t_dynarray argsarray	Array builder for `currentproc->args`
** @var t_dynarray inarray  	Array builder for `currentproc->inputs`
** @var t_dynarray outarray 	Array builder for `currentproc->outputs`
*/

typedef struct s_exprbuilder	t_exprbuilder;
struct		s_exprbuilder
{
	const char			*cursor;

	t_cmdexpr			*firstproc;
	t_cmdexpr			*currentproc;

	t_dynarray			argsarray;
	t_dynarray			inarray;
	t_dynarray			outarray;
};

/*
** Describes how to parse an element in a command.
** @var punc_none    	The next element is a standard argument.
** @var punc_append  	The next element is an output. (Append)
** @var punc_truncate	The next element is an output. (Truncate)
** @var punc_input   	The next element is an input.
** @var punc_pipe    	The next element is part of a new process.
** @var punc_end     	The next element is part of a new command.
*/

typedef enum e_punctuation		t_punctuation;
enum		e_punctuation
{
	punc_none = 0,
	punc_truncate = 1,
	punc_append = 2,
	punc_input = 3,
	punc_pipe = 4,
	punc_end = 5,
};

short		is_punctuation(char c);

void		parse_cmd(t_exprbuilder *builder);
short		exprbuild_init(t_exprbuilder *this, const char *cursor);
short		exprbuild_pipe(t_exprbuilder *this);
t_cmdexpr	*exprbuild_complete(t_exprbuilder *this);

#endif
