/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exprbuilder_abort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 18:01:00 by abaur             #+#    #+#             */
/*   Updated: 2020/09/05 18:01:00 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internals.h"

/*
** Frees everything that was allocated as a part of a failed builder.
** The builder itself is NOT freed.
** @param t_exprbuilder* this	The builder to clean.
*/

void	exprbuild_abort(t_exprbuilder *this)
{
	if (this->currentproc && this->currentproc->pipein)
		this->currentproc->pipein->pipeout = NULL;
	if (this->firstproc)
		procexpr_destroy(this->firstproc);
	if (this->argsarray.content)
	{
		freearrayn(&this->argsarray.content, this->argsarray.length);
		free(this->argsarray.content);
	}
	if (this->inarray.content)
	{
		freearrayn(&this->inarray.content, this->inarray.length);
		free(this->inarray.content);
	}
	if (this->outarray.content)
	{
		freearrayn(&this->outarray.content, this->outarray.length);
		free(this->outarray.content);
	}
	if (this->typearray.content)
		free(this->typearray.content);
}
