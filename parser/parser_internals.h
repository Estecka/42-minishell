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
** Environnement for parsing a command line.
** @var const char*const line  	The full line that contains the commands.
** @var const char*      cursor	The parser's current position within the comman
** d line.
**
** @var t_cmdexpr** processes  	The resulting array of process expressions.
** @var t_cmdexpr* prevproc   	The process that was previously being parsed in
**  the same command.
** @var t_cmdexpr* currentproc	The process expression being currently parsed.
**
** @var t_dynarray procarray	Array builder for `processes`.
** @var t_dynarray argsarray	Array builder for `currentproc->args`
** @var t_dynarray inarray  	Array builder for `currentproc->inputs`
** @var t_dynarray outarray 	Array builder for `currentproc->outputs`
*/

typedef struct s_exprbuilder	t_exprbuilder;
struct	s_exprbuilder
{
	const char*const	line;
	const char			*cursor;

	t_cmdexpr			*prevproc;
	t_cmdexpr			*currentproc;

	t_dynarray			procarray;
	t_dynarray			argsarray;
	t_dynarray			inarray;
	t_dynarray			outarray;
};

short	is_punctuation(char c);

char	**parse_args(const char **cursor);

#endif
