/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 15:44:00 by abaur             #+#    #+#             */
/*   Updated: 2020/10/09 15:44:00 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envvar.h"
#include "../libft/libft.h"

extern char		*validate_var_name(const char *name)
{
	if (!ft_strcmp(name, "?"))
		return (ft_strchr(name, '\0'));
	if (ft_isdigit(*name))
		return (char*)(name);
	while (ft_isalnum(*name) || *name == '_')
		name++;
	return (char*)(name);
}
