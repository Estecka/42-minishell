/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 15:23:50 by hherin            #+#    #+#             */
/*   Updated: 2020/10/19 13:30:42 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		valide_unset(char *args)
{
	int 
}

int		unset_built(int argc, char **args)
{
	size_t	i;
	
	i = 1;
	(void)argc;
	while (args[i])
	{
		if (!envclear(args[i]))
			return (0);
		i++;
	}
	return(0);
}