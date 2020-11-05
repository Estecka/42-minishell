/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 12:20:48 by hherin            #+#    #+#             */
/*   Updated: 2020/11/05 12:26:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

#ifdef __linux__
# include <wait.h>
#endif

short		free_all(char **tmp, char ***a_path)
{
	free(*tmp);
	free_mtab(a_path);
	return (0);
}

char		*get_path(char *args)
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
		return (tmp + free_all(&tmp, &a_path));
	while (a_path[++i])
	{
		if ((path = ft_strjoin(a_path[i], tmp)) && !stat(path, &buf))
			return (path + free_all(&tmp, &a_path));
		free(path);
	}
	free_all(&tmp, &a_path);
	return (NULL);
}

int			go_fork(int argc, char **args)
{
	pid_t		pid;
	int			status;
	struct stat	buf;

	(void)argc;
	status = 0;
	pid = fork();
	stat(args[0], &buf);
	if (!pid)
	{
		if (S_ISDIR(buf.st_mode) &&
				print_error("bash: line 1: exe: ", ": is a directoy\n", args[0]))
			exit(EXIT_FAILURE);
		else if (!(buf.st_mode & S_IXUSR) &&
				print_error("bash: line 1: exe: ", ": Permission denied\n",
					args[0]))
			exit(EXIT_FAILURE);
		else
			execve(args[0], args, (char**)(g_envarray.content));
	}
	else
		wait(&status); //retour signaux
	return (WEXITSTATUS(status));
}

t_builtin	command_exec(char **args)
{
	char		*path;
	char		*tmp;
	struct stat	buf;

	if (!(stat(args[0], &buf)))
		return (&go_fork);
	else
	{
		if ((path = get_path(args[0])))
		{
			tmp = args[0];
			args[0] = path;
			free(tmp);
			return (&go_fork);
		}
	}
	return (NULL);
}
