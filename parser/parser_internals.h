/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internals.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 15:28:00 by abaur             #+#    #+#             */
/*   Updated: 2020/11/15 17:07:34 by abaur            ###   ########.fr       */
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
	t_dynarray			ioarray;
	t_dynarray			typearray;
};

short		is_punctuation(char c);
short		append_single_quote(t_dynarray *chars, const char **cursor);
char		**reinsert_multivar(char **argaray, int argi, char *argv, int argc);
short		append_double_quote(t_dynarray *chars, const char **cursor);

short		parse_cmd(t_exprbuilder *builder);
short		exprbuild_init(t_exprbuilder *this, const char *cursor);
short		exprbuild_pipe(t_exprbuilder *this);
void		exprbuild_complete(t_exprbuilder *this);
void		exprbuild_abort(t_exprbuilder *this);

#endif
