/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internals.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 15:28:00 by abaur             #+#    #+#             */
/*   Updated: 2020/09/01 15:28:00 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INTERNALS_H
# define PARSER_INTERNALS_H

# include "parser.h"
# include "../libft/libft.h"
# include "../dynarray/dynarray.h"

short	is_punctuation(char c);
short	peek_argument(const char *s);

char	*next_arg(const char **cursor);

#endif
