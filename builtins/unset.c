/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 15:23:50 by hherin            #+#    #+#             */
/*   Updated: 2020/10/22 13:20:48 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int			unset_built(int argc, char **args)
{
	size_t	i;
	int		ret;
	size_t	equ;

	i = 1;
	(void)argc;
	while (args[i])
	{
		equ = ft_strlen(args[i]) - 1;
		if ((!ft_isalpha(args[i][0]) && args[i][0] != '_') ||
		args[i][equ] == '=')
			print_error("bash: unset: `", "': not a valid identifier", args[i]);
		else
			ret = envclear(args[i]);
		i++;
	}
	return (0);
}
