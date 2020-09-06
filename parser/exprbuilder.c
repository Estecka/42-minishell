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
	this->currentproc = malloc(sizeof(t_cmdexpr));
	dyninit(&this->argsarray, sizeof(char*), 4);
	dyninit(&this->inarray, sizeof(t_ioredir), 2);
	dyninit(&this->inarray, sizeof(t_ioredir), 2);
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
	this->currentproc = NULL;
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
	t_cmdexpr	*prevproc;
	t_ioredir	*pipeout;
	t_ioredir	*pipein;

	prevproc = this->currentproc;
	dynappendnull(&this->outarray);
	pipeout = (t_ioredir*)this->outarray.content;
	pipeout = &pipeout[this->outarray.length - 1];
	exprbuild_procend(this);
	exprbuild_procinit(this);
	pipeout->type = io_pipe;
	pipeout->target.expr = this->currentproc;
	dynappendnull(&this->inarray);
	pipein = (t_ioredir*)this->inarray.content;
	pipein->type = io_pipe;
	pipein->target.expr = prevproc;
	return (1);
}

/*
** Finalize the current command and returns it.
** @return t_cmdexpr*	The resulting process expressions.
*/

t_cmdexpr		*exprbuild_complete(t_exprbuilder *this)
{
	if (this->currentproc)
		exprbuild_procend(this);
	return (this->firstproc);
}
