/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 15:37:00 by abaur             #+#    #+#             */
/*   Updated: 2020/11/03 12:56:13 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../envvar/envvar.h"
#include "../libft/libft.h"
#include "builtins.h"

#include <errno.h>

/*
** Iterates over environnement variables in alphabetical order.
** @param const char* previous	The previously returned variable.
** 	Pass NULL in order to start from the beginning.
** @return char*	The following variable, or NULL if the last one was reached.
*/

static char	*get_next_var(const char *previous)
{
	const char	*worstguess;
	const char	*bestguess;
	const char	**cursor;

	worstguess = "\255";
	if (previous == NULL)
		previous = "\0";
	cursor = (const char**)g_envarray.content;
	bestguess = worstguess;
	while (*cursor)
	{
		if (ft_strccmp(bestguess, *cursor, '=') > 0
			&& ft_strccmp(previous, *cursor, '=') < 0)
			bestguess = *cursor;
		cursor++;
	}
	if (bestguess == worstguess)
		return (NULL);
	else
		return ((char*)bestguess);
}

static int	print_env(void)
{
	const char	*rawvar;
	const char	*separator;

	rawvar = NULL;
	while ((rawvar = get_next_var(rawvar)) != NULL)
	{
		separator = validate_var_name(rawvar);
		ft_putstr("declare -x ");
		write(1, rawvar, separator - rawvar);
		if (*separator)
		{
			ft_putstr("=\"");
			ft_putstr(separator + 1);
			ft_putchar('"');
		}
		ft_putchar('\n');
	}
	return (0);
}

static int	export_one(const char *var)
{
	size_t		namelen;
	const char	*valuestart;
	char		*raw;

	namelen = indexof('=', var);
	valuestart = validate_var_name(var);
	if ((*valuestart && *valuestart != '=' )|| valuestart == var)
		return (print_error("bash: export: `", "': not a valid identifier", \
				(char*)var));
	if (!(raw = ft_strdup(var)) || !set_env_var_raw(raw))
	{
		ft_putstr_fd("Unexpected error: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 2);
		return (errno);
	}
	return (0);
}

extern int	export_built(int argc, char **args)
{
	int status;
	int i;

	if (argc <= 1)
		return (print_env());
	status = 0;
	i = 1;
	while (i < argc)
	{
		status |= export_one(args[i]);
		i++;
	}
	return (status);
}
