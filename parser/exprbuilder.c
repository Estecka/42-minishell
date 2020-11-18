/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exprbuilder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 18:01:00 by abaur             #+#    #+#             */
/*   Updated: 2020/11/09 15:39:10 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internals.h"
#include "../libft/libft.h"
#include "../dynarray/dynarray.h"

/*
** Initializes a new process expression within the builder.
** In cas of error, the process may be left partially initialized, but is clean
** sable with exprbuild_abort.
** @return bool
** 	true 	OK
** 	false	error
*/

static short	exprbuild_procinit(t_exprbuilder *this)
{
	if ((this->currentproc = malloc(sizeof(t_procexpr)))
		&& dyninit(&this->argsarray, sizeof(char*), 4, 1)
		&& dyninit(&this->ioarray, sizeof(char*), 1, 1)
		&& dyninit(&this->typearray, sizeof(t_punctuation), 1, 1))
	{
		this->currentproc->pipein = NULL;
		this->currentproc->pipeout = NULL;
		return (1);
	}
	else
		return (0);
}

/*
** Finalizes the currently parsed process expression.
*/

static void		exprbuild_procend(t_exprbuilder *this)
{
	this->currentproc->argc = this->argsarray.length;
	this->currentproc->args = this->argsarray.content;
	this->currentproc->ioarray = this->ioarray.content;
	this->currentproc->iotypes = this->typearray.content;
	if (!this->firstproc)
		this->firstproc = this->currentproc;
	this->currentproc = NULL;
}

/*
** Initializes the builder with a process expression.
** If it fails, the builder should then be cleansed with exprbuild_abort.
** @return bool
** 	true 	OK
** 	false	error
*/

short			exprbuild_init(t_exprbuilder *this, const char *cursor)
{
	if (exprbuild_procinit(this))
	{
		this->cursor = cursor;
		return (1);
	}
	else
		return (0);
}

/*
** Closes the current process expression, and pipes it into a new one.
** @return bool	(To be implemented)
** 	true 	OK
** 	false	error
*/

short			exprbuild_pipe(t_exprbuilder *this)
{
	t_procexpr	*prevproc;

	prevproc = this->currentproc;
	exprbuild_procend(this);
	if (!exprbuild_procinit(this))
		return (0);
	prevproc->pipeout = this->currentproc;
	this->currentproc->pipein = prevproc;
	return (1);
}

/*
** Finalizes the current command.
** The result may then be recovered in this->firstproc.
*/

void			exprbuild_complete(t_exprbuilder *this)
{
	if (this->currentproc)
		exprbuild_procend(this);
}
