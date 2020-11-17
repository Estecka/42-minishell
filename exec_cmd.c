/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:40:45 by abaur             #+#    #+#             */
/*   Updated: 2020/11/17 20:56:21 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "builtin/builtins.h"
#include "parser/parser.h"
#include "stdrfd/stdrfd.h"

#include <errno.h>

#ifdef __linux__
# include <wait.h>
#endif

extern int		exec_cmd(int argc, char **argv)
{
	t_builtin	builtin;

	if (!argc)
		return (0);
	if (!argv[0])
		return (-1 | write(2, "[FATAL] Corrupted arg list.\n", 28));
	builtin = builtins_process(argv[0]);
	if (!builtin)
		builtin = command_exec(argv);
	if (builtin)
		return (builtin(argc, argv));
	else
	{
		print_error("bash: ligne 1: ", " : commande introuvable", argv[0]);
		return (127);
	}
}

static int		exec_process(t_procexpr *proc)
{
	int	status;

	proc->args = postproc_args_all(proc->args);
	proc->ioarray = postproc_args_all(proc->ioarray);
	status = bootstrap_fds(proc);
	if (!status)
		status = exec_cmd(proc->argc, proc->args);
	if (!restore_stdrfd())
	{
		ft_putstr_fd("restore_stdrfd failed", 2);
		ft_putendl_fd(strerror(errno), 2);
		status = errno;
	}
	return (status);
}

/*
** @param t_procexpr* proc	The expression of the process to create.
** @param int fdin	The fd the child process will listen to.
** @param int* fdout	Outputs the fd the next process should listen to, or 0 i
** f this was the last process in the chain.
** @return pid_t	The pid of the created child process.
*/

static pid_t	exec_fork(t_procexpr *proc, int fdin, int *fdout)
{
	pid_t	child;
	int		pipefds[2];
	int		status;

	ft_memset(pipefds, 0, sizeof(int[2]));
	if (proc->pipeout && pipe(pipefds) < 0)
		return (-1);
	*fdout = pipefds[0];
	child = fork();
	errno = 0;
	if (child)
	{
		if (proc->pipeout)
			close(pipefds[1]);
		return (child);
	}
	g_is_subprocess = 1;
	if (pipefds[0])
		close(pipefds[0]);
	if (fdin && ((dup2(fdin, 0) < 0) || close(fdin)))
		clean_exit(errno);
	if (pipefds[1] && ((dup2(pipefds[1], 1) < 0) || close(pipefds[1])))
		clean_exit(errno);
	status = exec_process(proc);
	exit(clean_exit(status));
}

static int		exec_pipechain(t_procexpr *chain)
{
	pid_t	last;
	int		pipein;
	int		pipeout;
	int		status;

	pipein = 0;
	while (chain)
	{
		last = exec_fork(chain, pipein, &pipeout);
		if (pipein)
			close(pipein);
		pipein = pipeout;
		chain = chain->pipeout;
		errno = 0;
	}
	waitpid(last, &status, 0);
	status = WEXITSTATUS(status);
	while (wait(&(int){0}) > -1)
		;
	if (errno == ECHILD)
		errno = 0;
	return (status);
}

extern int		execute_cmds_all(t_procexpr **cmdarray)
{
	t_procexpr	**cmd;

	cmd = cmdarray;
	while (*cmd)
	{
		errno = 0;
		if (!(*cmd)->pipeout)
			g_prev_status = exec_process(*cmd);
		else
			g_prev_status = exec_pipechain(*cmd);
		cmd++;
	}
	if (cmdarray)
		procexpr_destroy_all(cmdarray);
	return (g_prev_status);
}
