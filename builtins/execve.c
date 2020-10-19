/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 12:20:48 by hherin            #+#    #+#             */
/*   Updated: 2020/10/19 13:23:53 by hherin           ###   ########.fr       */
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
	{
		free(tmp);	
		free_mtab(&a_path);
		return (tmp);
	}
	while (a_path[++i])
	{
		if ((path = ft_strjoin(a_path[i], tmp)) && !stat(path, &buf))
		{
			free(tmp);
			free_mtab(&a_path);
			return (path);
		}
		free(path);
	}
	free(tmp);
	free_mtab(&a_path);
	return (NULL);
}

int				go_fork(int argc, char **args)
{
	pid_t		pid;
	int			status;
	struct stat	buf;

	(void)argc;
	pid = fork();
	stat(args[0], &buf);
	if (!pid)
	{
		if (S_ISDIR(buf.st_mode) && 
				print_error("minishell: exe: ", ": is a directoy\n", args[0]))
			exit(EXIT_FAILURE);
		else if (!(buf.st_mode & S_IXUSR) && 
				print_error("minishell: exe: ", ": Permission denied\n", args[0]))
			exit(EXIT_FAILURE);
		else
		{
			execve(args[0], args, (char**)(g_envarray.content));
			exit(EXIT_SUCCESS);
		}
	}
	else
		wait(&status);
	return(errno);
}

t_builtin		command_exec(char **args)
{
	char		*path;
	char		*tmp;
	struct stat	buf;

	if (!(stat(args[0], &buf)))
		return(&go_fork);
	else
	{
		if ((path = get_path(args[0])))
		{
			tmp = args[0];
			args[0] = path;
			free(tmp);
			return(&go_fork);
		}
	}
	return (NULL);
}
