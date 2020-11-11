/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:11:43 by abaur             #+#    #+#             */
/*   Updated: 2020/11/11 19:19:25 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "envvar.h"

short	isset_envvar(const char *name)
{
	const char **cursor;

	cursor = (const char**)g_envarray.content;
	while (*cursor)
		if (!ft_strccmp(name, *cursor, '='))
			return (1);
	return (0);
}
