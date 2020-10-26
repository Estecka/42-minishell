/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:40:45 by abaur             #+#    #+#             */
/*   Updated: 2020/10/26 14:35:15 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "builtins/builtins.h"
#include "parser/parser.h"
#include "stdrfd/stdrfd.h"

#include <errno.h>

extern int	exec_cmd(int argc, char **argv)
{
	t_builtin	builtin;

	if (!argv[0])
		return (-1 | write(2, "[FATAL] Corrupted arg list.\n", 28));
	builtin = builtins_process(argv[0]);
	if (!builtin)
		builtin = command_exec(argv);
	if (builtin)
		return (builtin(argc, argv));
	else
		return (127 & print_error("bash: ", ": command not found\n", argv[0]));
}

static int	exec_process(t_procexpr *proc)
{
	int	status;

	postproc_args_all(proc->args);
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

static int	exec_pipechain(t_procexpr *chain)
{
	return (exec_process(chain));
}

extern int	execute_cmds_all(t_procexpr **cmdarray)
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
