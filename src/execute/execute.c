/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:10:54 by numartin          #+#    #+#             */
/*   Updated: 2023/07/11 15:28:19 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_state		g_state;

static void	execute_cmd(char **cmd)
{
	int		pid;
	int		status;

	if (!cmd[0] || !path(cmd[0], g_state.envp))
		return ;
	pid = fork();
	define_exec_signals();
	if (pid == 0)
	{
		array_env(&g_state);
		execve(cmd[0], cmd, g_state.envp);
		free_split(g_state.envp);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_state.exit_status = WEXITSTATUS(status);
}

void	execute(char **cmd)
{
	int	i;

	i = 0;
	if (is_builtin(cmd))
		execute_builtin(&cmd[i], &g_state);
	else
		execute_cmd(&cmd[i]);
}
