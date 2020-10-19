/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 15:23:50 by hherin            #+#    #+#             */
/*   Updated: 2020/10/19 11:56:25 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		unset_built(int argc, char **args)
{
	size_t	i;
	
	i = 1;
	(void)argc;
	while (args[i])
	{
		envclear(args[i]);
		i++;
	}
	return(0);
}