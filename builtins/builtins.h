/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 14:44:48 by hherin            #+#    #+#             */
/*   Updated: 2020/10/19 11:17:35 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/errno.h>
# include "../libft/libft.h"
# include "../envvar/envvar.h"
# include <sys/stat.h>
# include <string.h>
# include <stdio.h>

typedef int (*t_builtin)(int argc, char **args);

int			echo_built(int argc, char **args);
int			pwd_built(int argc, char **args);
int			env_built(int argc, char **args);
int			cd_built(int argc, char **args);
int			exit_built(int argc, char **args);
int			export_built(int argc, char **args);
int			unset_built(int argc, char **args);
t_builtin	command_exec(char **args);
t_builtin	builtins_process(char *name);

char		*home_dir(char *args);
void		free_mtab(char ***tab);
int			print_error(char *s1, char *s2, char *args);
long long	ft_atoi_ll(const char *str);

#endif