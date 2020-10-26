/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:40:45 by abaur             #+#    #+#             */
/*   Updated: 2020/10/21 15:55:39 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "builtins/builtins.h"
#include "parser/parser.h"
#include "stdrfd/stdrfd.h"

int	exec_cmd(int argc, char **argv)
{
	t_builtin	builtin;
	
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

	cmd = cmdarray;
	while (*cmd)
	{
		postproc_args_all((*cmd)->args);
		g_prev_status = bootstrap_fds(*cmd);
		if (!g_prev_status)
			g_prev_status = exec_cmd((*cmd)->argc, (*cmd)->args);
		cmd++;
		if (!restore_stdrfd())
		{
			ft_putstr_fd("restore_stdrfd failed", 2);
			ft_putstr_fd(strerror(errno), 2);
		}
	}
	if (cmdarray)
		procexpr_destroy_all(cmdarray);
	return (g_prev_status);
}
