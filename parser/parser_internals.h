/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internals.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 15:28:00 by abaur             #+#    #+#             */
/*   Updated: 2020/11/16 23:50:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INTERNALS_H
# define PARSER_INTERNALS_H

# include "parser.h"

# include <errno.h>

# include "../libft/libft.h"
# include "../dynarray/dynarray.h"

/*
** Environnement for parsing a single command. (';' separated)
** @var const char* cursor	The parser's current position within the command li
** ne.
**
** @var t_procexpr* firstproc  	The first process in the command.
** 	This acts as the "return value" of the builder.
** @var t_procexpr* currentproc	The process being currently parsed.
**
** @var t_dynarray argsarray	Array builder for `currentproc->args`
** @var t_dynarray inarray  	Array builder for `currentproc->inputs`
** @var t_dynarray outarray 	Array builder for `currentproc->outputs`
** @var t_dynarray outarray 	Array builder for `currentproc->outtypes`
*/

typedef struct s_exprbuilder	t_exprbuilder;
struct		s_exprbuilder
{
	const char			*cursor;

	t_procexpr			*firstproc;
	t_procexpr			*currentproc;

	t_dynarray			argsarray;
	t_dynarray			inarray;
	t_dynarray			outarray;
	t_dynarray			typearray;
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
short		append_single_quote(t_dynarray *chars, const char **cursor);
short		append_double_quote(t_dynarray *chars, const char **cursor);

short		parse_cmd(t_exprbuilder *builder);
short		exprbuild_init(t_exprbuilder *this, const char *cursor);
short		exprbuild_pipe(t_exprbuilder *this);
void		exprbuild_complete(t_exprbuilder *this);
void		exprbuild_abort(t_exprbuilder *this);

void			ch_envvar(int sp, char out);
char**     post_varproc(char **args);
#endif
