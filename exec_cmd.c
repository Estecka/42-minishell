/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:40:45 by abaur             #+#    #+#             */
/*   Updated: 2020/10/22 12:43:17 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "builtins/builtins.h"
#include "parser/parser.h"
#include "stdrfd/stdrfd.h"

#include <errno.h>

int	exec_cmd(int argc, char **argv)
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

int	execute_cmds_all(t_procexpr **cmdarray)
{
	t_procexpr	**cmd;
	int			status;

	cmd = cmdarray;
	while (*cmd)
	{
		errno = 0;
		postproc_args_all((*cmd)->args);
		status = bootstrap_fds(*cmd);
		if (!status)
			g_prev_status = exec_cmd((*cmd)->argc, (*cmd)->args);
		else
			g_prev_status = status;
		cmd++;
		if (!restore_stdrfd())
		{
			ft_putstr_fd("restore_stdrfd failed", 2);
			ft_putendl_fd(strerror(errno), 2);
		}
	}
	if (cmdarray)
		procexpr_destroy_all(cmdarray);
	return (g_prev_status);
}
