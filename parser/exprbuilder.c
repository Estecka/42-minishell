/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exprbuilder                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 18:01:00 by abaur             #+#    #+#             */
/*   Updated: 2020/09/05 18:01:00 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internals.h"
#include "../libft/libft.h"
#include "../dynarray/dynarray.h"

/*
** Initializes a new process expression within the builder.
** @return bool	(To be implemented)
** 	true 	OK
** 	false	error
*/

static short	exprbuild_procinit(t_exprbuilder *this)
{
	this->currentproc = malloc(sizeof(t_procexpr));
	this->currentproc->pipein = NULL;
	this->currentproc->pipeout = NULL;
	dyninit(&this->argsarray, sizeof(char*), 4);
	dyninit(&this->inarray, sizeof(char*), 2);
	dyninit(&this->outarray, sizeof(char*), 2);
	dyninit(&this->typearray, sizeof(short), 2);
	return (1);
}

/*
** Finalizes the currently parsed process expression.
** @return bool	(To be implemented)
** 	true 	OK
** 	false	error
*/

static short	exprbuild_procend(t_exprbuilder *this)
{
	this->currentproc->args = dynappendnull(&this->argsarray);
	this->currentproc->inputs = dynappendnull(&this->inarray);
	this->currentproc->outputs = dynappendnull(&this->outarray);
	this->currentproc->outtypes = dynappendnull(&this->typearray);
	this->currentproc = NULL;
	return (1);
}

/*
** Initializes the builder with a process expression.
** @return bool	(To be implemented)
** 	true 	OK
** 	false	error
*/

short			exprbuild_init(t_exprbuilder *this, const char *cursor)
{
	exprbuild_procinit(this);
	this->firstproc = this->currentproc;
	this->cursor = cursor;
	return (1);
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
	exprbuild_procinit(this);
	prevproc->pipeout = this->currentproc;
	this->currentproc->pipein = prevproc;
	return (1);
}

/*
** Finalize the current command and returns it.
** @return t_procexpr*	The resulting process expressions.
*/

t_procexpr		*exprbuild_complete(t_exprbuilder *this)
{
	if (this->currentproc)
		exprbuild_procend(this);
	return (this->firstproc);
}
