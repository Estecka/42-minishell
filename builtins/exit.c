/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 12:05:31 by hherin            #+#    #+#             */
/*   Updated: 2020/10/15 17:36:23 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		exit_built(int argc, char **args)
{
    // (void)argc;
    (void)args;
    if (argc > 1)
    {
        
    }
    printf("argc %d\n", argc);
    write(1, "exit\n", 5);
    exit(EXIT_SUCCESS);
    return (0);
}