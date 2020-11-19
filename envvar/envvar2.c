/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:11:43 by abaur             #+#    #+#             */
/*   Updated: 2020/11/19 18:30:23 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "envvar.h"

short		isset_envvar(const char *name)
{
	const char **cursor;

	cursor = (const char**)g_envarray.content - 1;
	while (*++cursor)
		if (!ft_strccmp(name, *cursor, '='))
			return (1);
	return (0);
}

const char	*get_envvar_rdonly(const char *name)
{
	const char	**cursor;
	const char	*result;

	cursor = (const char**)g_envarray.content - 1;
	while (*++cursor)
		if (!ft_strccmp(name, *cursor, '='))
		{
			result = validate_var_name(*cursor);
			if (*result == '=')
				return (result + 1);
			else
				return (result);
		}
	return ("");
}
