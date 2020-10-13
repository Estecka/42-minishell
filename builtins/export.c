/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 15:37:00 by abaur             #+#    #+#             */
/*   Updated: 2020/10/13 15:37:00 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../envvar/envvar.h"
#include "../libft/libft.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static int	print_env(void)
{
	printf("Functionnality not yet implemented\n");
	return (-1);
}

static int	export_one(const char *var)
{
	size_t		namelen;
	const char	*valuestart;
	char		*raw;

	namelen = indexof('=', var);
	valuestart = validate_var_name(var);
	if (*valuestart && *valuestart != '=')
	{
		write(2, "not valid in this context: ", 28);
		write(2, var, namelen);
		write(2, "\n", 1);
		return (1);
	}
	if (!(raw = ft_strdup(var)) || !set_env_var_raw(raw))
	{
		ft_putstr_fd("Unexpected error: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 2);
		return (errno);
	}
	return (0);
}

extern int	export_built(int argc, char*const *args)
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
