/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multivar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 16:28:51 by abaur             #+#    #+#             */
/*   Updated: 2020/11/17 20:04:39 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internals.h"

static char	*next_substring(const char *metastring)
{
	while (*metastring)
		metastring++;
	return (char*)(metastring + 1);
}

static char	**realloc_argarray(char **argarray, int argi, int argc)
{
	char	**result;
	int		arraylen;

	arraylen = ft_ptrlen((const void**)argarray);
	result = malloc(sizeof(char*) * (argc + arraylen));
	if (!result)
		return (NULL);
	ft_memcpy(result, argarray, argi * sizeof(char*));
	ft_memcpy(result + argi + argc, argarray + argi + 1,
		(arraylen - argi - 1) * sizeof(char*));
	result[arraylen + argc - 1] = NULL;
	free(argarray[argi]);
	free(argarray);
	return (result);
}

/*
** Replaces a single argument with multiple arguments.
** @param char** argarray	The array where to reinsert the arguments.
** 	This pointer will be freed in case of success.
** @param int argi	The index of the argument to replace.
** 	This argument will be freed in case of success.
** @param char* argv	The metastring containing all the arguments to insert.
** @param int argc	The amount of arguments in the metastring.
** @return char**	A reallocated copy of the argument array, or NULL if an erro
** r occured
*/

char		**reinsert_multivar(char **argarray, int argi, char *argv, int argc)
{
	char	**result;
	char	**cursor;

	result = realloc_argarray(argarray, argi, argc);
	if (!result)
		return (NULL);
	cursor = result + argi;
	while (argc)
	{
		*cursor = ft_strdup(argv);
		argv = next_substring(argv);
		argc--;
		cursor++ ;
	}
	return (result);
}
