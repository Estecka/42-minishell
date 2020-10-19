/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 15:23:50 by hherin            #+#    #+#             */
/*   Updated: 2020/10/19 13:45:49 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		unset_built(int argc, char **args)
{
	size_t	i;
	int		ret;
	
	i = 1;
	(void)argc;
	while (args[i])
	{
		if (!ft_isalpha(args[i][0]) && args[i][0] != '_')
		{
			print_error("bash: unset: `", "': not a valid identifier", args[i]);
			return (1);
		}
		ret = envclear(args[i]);
		i++;
	}
	return(0);
}