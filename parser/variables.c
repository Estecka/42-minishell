/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 11:50:00 by abaur             #+#    #+#             */
/*   Updated: 2020/10/21 13:52:51 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internals.h"

/*
** Parses the name of an environnement variable within an argument.
** The special variable name $? is supported.
** @param char** cursor	A cursor to the '$' preceding the variable's name.
** 	This cursor will be moved to the first character following the name.
** 	Its value will be undefined in case of error.
** @return char*	A allocated copy of the name, or NULL in case of error.
*/

static char		*get_var_name(const char **cursor)
{
	t_dynarray	name;

	++*cursor;
	if (**cursor == '?')
	{
		(*cursor)++;
		return (ft_strdup("?"));
	}
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
** @param t_dynarray* narg	The stringbuilder that contains the newly formed arg
** ument.
** @param char** cursor	A cursor to the '$' preceding the variable's name.
** 	On success, it will point to the last character of the variable's name.
** @return
** 	true 	OK
** 	false	Error
*/

static short	append_var(t_dynarray *narg, const char **cursor)
{
	char	*varname;
	char	*varvalue;
	short	r;

	varname = get_var_name(cursor);
	(*cursor)--;
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

extern char		*postproc_arg(const char *arg)
{
	t_dynarray	narg;
	char		quote;

	if (!dyninit(&narg, sizeof(char), ft_strlen(arg), 1))
		return (NULL);
	quote = 0;
	while(*arg && !errno)
	{
		if (!quote && (*arg == '\'' || *arg == '\"'))
			quote = *arg;
		else if (quote && *arg == quote)
			quote = 0;
		else if (quote != '\'' && *arg == '$')
			append_var(&narg, &arg);
		else if (*arg == '\\' && (!quote || ft_strcontain("\"\\$", *(arg + 1))))
			dynappend(&narg, &*++arg);
		else 
			dynappend(&narg, &*arg);
		arg++;
	}
	if (errno)
		free(narg.content);
	return (char*)((!errno) * (long)narg.content);
}

void		postproc_args_all(char **args)
{
	int		i;
	char	*r;

	i = 0;
	while (args[i])
	{
		r = postproc_arg(args[i]);
		free(args[i]);
		args[i] = r;
		i++;
	}
}