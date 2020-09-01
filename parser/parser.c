/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 16:23:00 by abaur             #+#    #+#             */
/*   Updated: 2020/08/30 16:23:00 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../libft/libft.h"
#include "../get_next_line/get_next_line.h"
#include "../dynarray/dynarray.h"

/*
** Extracts the next argument from the string, and advances the cursors accordi
** ngly.
** @param char** cursor	A pointer to where to start seeking the next argument.
** 	This pointer is moved after the end of the argument on return.
** @return char*	The found argument or NULL if none were found.
*/

static char	*next_arg(const char **cursor)
{
	t_dynarray chars;

	dyninit(&chars, sizeof(char), 8);
	while (**cursor && ft_isspace(**cursor))
		(*cursor)++;
	while (**cursor && !ft_isspace(**cursor))
	{
		dynappend(&chars, &(**cursor));
		(*cursor)++;
	}
	if (chars.length > 0)
		return (chars.content);
	free(chars.content);
	return (NULL);
}

/*
** Breaks a string down into an array of arguments.
** @param const char* line	The string to break down.
** @return char**	An array of arguments.
*/

static char	**split_args(const char *line)
{
	t_dynarray	args;
	char		*current_arg;

	dyninit(&args, sizeof(char*), 8);
	while (*line)
	{
		current_arg = next_arg(&line);
		dynappend(&args, &current_arg);
	}
	dynappend(&args, &(char*){NULL});
	return (char**)(args.content);
}

extern int	get_next_expr(t_cmdexpr *expr)
{
	char	*line;
	int		err;

	err = get_next_line(0, &line);
	if (err < 0)
		return (err);
	*expr = (t_cmdexpr){ 0 };
	if (line)
	{
		expr->args = (const char**)split_args(line);
		free(line);
	}
	return (err);
}
