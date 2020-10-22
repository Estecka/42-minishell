/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 11:36:36 by hherin            #+#    #+#             */
/*   Updated: 2020/10/22 13:01:26 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_builtin			builtins_process(char *name)
{
	if (!ft_strcmp(name, "export"))
		return (&export_built);
	else if (!ft_strncmp(name, "echo", 5))
		return (&echo_built);
	else if (!ft_strncmp(name, "pwd", 4))
		return (&pwd_built);
	else if (!ft_strncmp(name, "env", 4))
		return (&env_built);
	else if (!ft_strncmp(name, "cd", 3))
		return (&cd_built);
	else if (!ft_strncmp(name, "exit", 5))
		return (&exit_built);
	else if (!ft_strncmp(name, "unset", 6))
		return (&unset_built);
	else
		return (NULL);
}
