/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 12:20:48 by hherin            #+#    #+#             */
/*   Updated: 2020/10/15 18:04:05 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char			*get_path(char *args)
{
	char		*path;
	char		*tmp;
	char		**a_path;
	int			i;
	struct stat	buf;
	
	path = get_env_var("PATH");
	a_path = ft_split(path, ':');
	free(path);
	i = -1;
	tmp = (!ft_strncmp(args, "~", 1)) ? home_dir(args) : ft_strjoin("/", args);
	if (!stat(tmp, &buf))
		return (tmp);
	while (a_path[++i])
	{
		if ((path = ft_strjoin(a_path[i], tmp)) && !stat(path, &buf))
		{
			return (path);
			free_mtab(&a_path);
		}
		free(path);
	}
	free(tmp);
	free_mtab(&a_path);
	return (NULL);
}

int			go_fork(char **args)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (!pid)
	{
		execve(args[0], args, (char**)(g_envarray.content));
		return (errno);
	}
	else
		wait(&status);
	return(errno);
}

int			execve_cmd(int argc, char **args)
{
	struct stat	buf;
	char		*path;
	char		*tmp;

	(void)argc;
	tmp = NULL;
	if (!(stat(args[0], &buf)))
		go_fork(args);
	else
	{
		path = get_path(args[0]);
		if ((path))
		{	
			tmp = args[0];
			args[0] = path;
			free(tmp);
			go_fork(args);
		}
		else
			printf("bash: %s: %s\n", args[0], strerror(errno));
	}
	return (errno);
}


t_builtin     command_exec(void)
{
	// system("leaks minishell");
	return(&execve_cmd);
}

//  /Users/hherin/Minishell/dynarray