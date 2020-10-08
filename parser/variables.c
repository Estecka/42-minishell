/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 11:50:00 by abaur             #+#    #+#             */
/*   Updated: 2020/10/06 11:50:00 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internals.h"

/*
** Parses the name of an environnement variable within an argument.
** @param char** cursor	A cursor to the '$' preceding the variable's name.
** 	This cursor will be moved to the first character following the name.
** 	Its value will be undefined in case of error.
** @return char*	A allocated copy of the name, or NULL in case of error.
*/

static char		*get_var_name(char **cursor)
{
	t_dynarray	name;

	++*cursor;
	if (!dyninit(&name, sizeof(char), 8, 1))
		return (NULL);
	while (ft_isalnum(**cursor) || **cursor == '_')
	{
		if (!dynappend(&name, &**cursor))
		{
			free(name.content);
			return (NULL);
		}
		(*cursor)++;
	}
	return (name.content);
}

/*
** Replaces a single variable's name with its value.
** @param t_dynarray* narg	The stringbuilder that contains the newly formed argume
** nt.
** @param char** cursor	A cursor to the '$' preceding the variable's name.
** @return
** 	true 	OK
** 	false	Error
*/

static short	append_var(t_dynarray *narg, char **cursor)
{
	char	*varname;
	char	*varvalue;
	short	r;

	varname = get_var_name(cursor);
	if (!varname)
		return (0);
	varvalue = get_env_var(varname);
	if (!varvalue)
	{
		free(varname);
		return (0);
	}
	r = (dynappendn(narg, varvalue, ft_strlen(varvalue)) != NULL);
	free(varname);
	free(varvalue);
	return (r);
}

/*
** Seek all variable names in an argument and replaces them with their values.
** @param char* arg	The argument to parse. Will be freed.
** @return char*	The argument's final form.
*/

extern char		*postproc_arg(char *arg)
{
	t_dynarray	narg;
	char		*cursor;

	if (!dyninit(&narg, sizeof(char), ft_strlen(arg), 1))
		return (NULL);
	cursor = arg;
	while(*cursor)
	{
		if (*cursor != '$')
		{
			if (*cursor == '\\' && *(cursor + 1))
				cursor++;
			dynappend(&narg, cursor);
			cursor++;
		}
		else if (!append_var(&narg, &cursor))
		{
			free(narg.content);
			return (NULL);
		}
	}
	free (arg);
	return (narg.content);
}
