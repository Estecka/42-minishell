/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 14:44:48 by hherin            #+#    #+#             */
/*   Updated: 2020/10/09 11:44:56 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/errno.h>
# include "../libft/libft.h"

#include <stdio.h>

int		echo_built(char **args);
int		pwd_built(char **args);
int		env_built(char **args, char *env[]);
int		builtins_process(char **args, char *env[]);

#endif