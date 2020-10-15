/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 16:46:03 by hherin            #+#    #+#             */
/*   Updated: 2020/10/15 17:52:52 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char		*home_dir(char *args)
{
	char *tmp;
    char    *add_slash;
	char *dir;

	tmp = get_env_var("HOME");
    add_slash = ft_strjoin(tmp, "/");
	dir = ft_strjoin(add_slash, args + 2);
	free(tmp);
    free(add_slash);
	return (dir);
}

void        free_mtab(char ***tab)
{
    int     i;

    i = 0;
    while ((*tab)[i])
    {
        free((*tab)[i]);
        i++;
    }
    free((*tab));
}