/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 12:20:48 by hherin            #+#    #+#             */
/*   Updated: 2020/11/19 18:30:11 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

#ifdef __linux__
# include <wait.h>
#endif

short		free_all(char **tmp, char ***a_path, char **tmp2)
{
	(tmp2) ? free(*tmp2) : 0;
	(tmp) ? free(*tmp) : 0;
	(a_path) ? free_mtab(a_path) : 0;
	return (0);
}

char		*get_path(char *args, const char *envpath)
{
	char		*path;
	char		*tmp[2];
	char		**a_path;
	int			i;
	struct stat	buf;

	a_path = ft_split(envpath, ':');
	i = -1;
	tmp[0] = (!ft_strncmp(args, "~", 1)) ? home_dir(args) : ft_strdup(args);
	tmp[1] = ft_strjoin("/", tmp[0]);
	while (a_path[++i])
	{
		if ((path = ft_strjoin(a_path[i], tmp[1])) && !stat(path, &buf))
			return (path + free_all(&tmp[0], &a_path, &tmp[1]));
		free(path);
	}
	if (!stat(tmp[0], &buf) && (!ft_strncmp(tmp[0], "./", 2) ||
	!ft_strncmp(tmp[0], "..", 2) || !ft_strncmp(tmp[0], "/", 1)))
		return (tmp[0] + free_all(&tmp[0], &a_path, &tmp[1]));
	free_all(&tmp[0], &a_path, &tmp[1]);
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
		if (S_ISDIR(buf.st_mode)
			&& print_error("bash: line 1: exe: ", ": is a directoy\n", args[0]))
			exit(EXIT_FAILURE);
		else if (!(buf.st_mode & S_IXUSR) &&
				print_error("bash: line 1: exe: ", ": Permission denied\n",
					args[0]))
			exit(EXIT_FAILURE);
		else
			execve(args[0], args, (char**)(g_envarray.content));
	}
	else
		wait(&status);
	return (WEXITSTATUS(status));
}

t_builtin	command_exec(char **args)
{
	char		*path;
	const char	*envpath;
	char		*tmp;
	struct stat	buf;

	envpath = get_envvar_rdonly("PATH");
	if (*envpath && !(stat(args[0], &buf)) && (!ft_strncmp(args[0], "./", 2)
	|| !ft_strncmp(args[0], "..", 2) || !ft_strncmp(args[0], "/", 1)))
		return (&go_fork);
	else if (*envpath && (path = get_path(args[0], envpath)))
	{
		tmp = args[0];
		args[0] = path;
		free(tmp);
		return (&go_fork);
	}
	else if (!(*envpath) && !(stat(args[0], &buf)))
		return (&go_fork);
	return (NULL);
}
