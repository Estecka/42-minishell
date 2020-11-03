/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:32:49 by heleneherin       #+#    #+#             */
/*   Updated: 2020/11/03 18:15:00 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envvar.h"
#include "../libft/libft.h"
#include "../builtin/builtins.h"
#include <stdio.h>

static int	is_stringalpha(const char *s)
{
	int i;

	i = -1;
	while (s[++i])
	{
		if (ft_isalpha(s[i]))
			return (1);
	}
	return (0);
}

void	shell_level(void)
{
	char **env;
	int		level;
	char	*lvl;

	env = (char**)(g_envarray.content);
	lvl = get_env_var("SHLVL");
	level = ft_atoi(lvl) + 1;
	if (is_stringalpha(lvl) || !*(lvl))
		set_env_var("SHLVL", "1");
	else
	{
		free(lvl);
		if (level > 1000)
		{
			print_error("bash: warning: shell level (", "1001) too high, resetting to 1", "");
			set_env_var("SHLVL", "1");
		}
		else
		{
			lvl = ft_itoa(level);
			set_env_var("SHLVL", lvl);
			free(lvl);
		}
	}
	printf("var %s\n", get_env_var("SHLVL"));
}

// checker si chaine caract ou nombre