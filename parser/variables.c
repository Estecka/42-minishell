/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 11:50:00 by abaur             #+#    #+#             */
/*   Updated: 2020/11/17 19:28:25 by abaur            ###   ########.fr       */
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

static char	*get_var_name(const char **cursor)
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

static int	append_multivar(t_dynarray *narg, const char *varvalue)
{
	int r;

	r = 0;
	varvalue--;
	while (*++varvalue)
	{
		if (ft_isspace(*varvalue))
		{
			dynappendnull(narg);
			varvalue = ft_skipspace(varvalue) - 1;
			r++;
		}
		else
			dynappend(narg, &*varvalue);
	}
	return (r);
}

/*
** Replaces a single variable's name with its value.
** If the variable is not under quotes, the parsed argument may turn into multip
** le ones. In which case, the formed string will contains all the arguments, se
** parated with null-terminators.
** @param t_dynarray* narg	The stringbuilder that contains the newly formed arg
** ument.
** @param char** cursor	A cursor to the '$' preceding the variable's name.
** 	On success, it will point to the last character of the variable's name.
** @param bool quote	Wether the variable is under quotes.
** @return int	The amount of NEW arguments created in the process.
** 	This will always be underquotes
*/

static int	append_var(t_dynarray *narg, const char **cursor, short quote)
{
	char	*varname;
	char	*varvalue;
	int		r;

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
	r = 0;
	if (quote)
		dynappendn(narg, varvalue, ft_strlen(varvalue));
	else
		r = append_multivar(narg, varvalue);
	free(varname);
	free(varvalue);
	return (r);
}

/*
** Parses a raw argument into its final form.
** This involves replacing variables name, escaped characters, and quotes.
** This may result into a single argument splitting into multiple ones, in which
**  case the resulting string will contain multiple null-terminators.
** @param const char* arg	The raw argument to parse.
** @param char** result	Outputs the resulting string, or NULL if an error occure
** d.
** @param char quote	Must be 0.
** @param int argc	Must be 1.
** @return int	The total amount of arguments (and thus null-terminators) in the
**  resulting string. Or 0 if an error occured.
*/

static int	postproc_arg(const char *arg, char **dst, char quote, int argc)
{
	t_dynarray	narg;

	if (!dyninit(&narg, sizeof(char), ft_strlen(arg), 1))
		return (0);
	while (*arg && !errno)
	{
		if (!quote && (*arg == '\'' || *arg == '\"'))
			quote = *arg;
		else if (quote && *arg == quote)
			quote = 0;
		else if (quote != '\'' && *arg == '$')
			argc += append_var(&narg, &arg, quote);
		else if (quote != '\'' && *arg == '\\'
			&& (!quote || ft_strcontain("\"\\$", *(arg + 1))))
			dynappend(&narg, &*++arg);
		else
			dynappend(&narg, &*arg);
		arg++;
	}
	if (errno)
		free(narg.content);
	*dst = (errno ? NULL : narg.content);
	return (errno ? 0 : argc);
}

char		**postproc_args_all(char **args)
{
	int		i;
	char	*argv;
	int		argc;

	i = 0;
	while (args[i])
	{
		argc = postproc_arg(args[i], &argv, 0, 1);
		if (argc <= 0)
			return (NULL);
		if (argc == 1)
		{
			free(args[i]);
			args[i] = argv;
		}
		else if (argc > 1)
			args = reinsert_multivar(args, i, argv, argc);
		i++;
	}
	return (args);
}
