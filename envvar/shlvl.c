/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:32:49 by heleneherin       #+#    #+#             */
/*   Updated: 2020/11/05 15:25:35 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envvar.h"
#include "../libft/libft.h"
#include "../builtin/builtins.h"

static int	is_stringalpha(const char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]) && !(i == 0 && (s[i] == '-' || s[i] == '+')))
			return (1);
		i++;
	}
	return (0);
}

void		shell_level(void)
{
	char	**env;
	int		level;
	char	*lvl;

	env = (char**)(g_envarray.content);
	lvl = get_env_var("SHLVL");
	level = ft_atoi(lvl);
	if (is_stringalpha(lvl)
		|| !*(lvl)
		|| (!is_stringalpha(lvl) && level >= 1000))
	{
		(level > 1000) ? print_error("bash: warning: shell level (",
			"1001) too high, resetting to 1", "") : 0;
		set_env_var("SHLVL", "1");
	}
	else
	{
		free(lvl);
		lvl = (level < 0) ? ft_itoa(0) : ft_itoa(level + 1);
		set_env_var("SHLVL", lvl);
		free(lvl);
	}
}
