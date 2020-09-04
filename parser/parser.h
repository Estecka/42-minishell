/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:38:42 by abaur             #+#    #+#             */
/*   Updated: 2020/01/28 16:12:34 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"

/*
** Fetches the next expression from stdin.
** @param t_cmdexpr* expr	Outputs the resulting expression.
** @param char**	Outputs the full string that contains the command.
** @return int	The return value from get_next_line.
*/

int	get_next_expr_legacy(t_cmdexpr *expr, char **cmd);

/*
** Parses all commands in the given line.
** @param char* line	The full line that contains the commands.
** @return t_cmdexpr*	An array of command expressions.
*/
t_cmdexpr	**get_next_cmdline(const char *line);

#endif
