/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:10:54 by numartin          #+#    #+#             */
/*   Updated: 2023/07/11 16:32:01 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_state		g_state;

static int	is_path_defined(char **path_variable)
{
	t_env	*path;

	path = findenv(&g_state, "PATH");
	if (!path)
	{
		print_error("no such file or directory.", 127);
		return (0);
	}
	*path_variable = path->value;
	return (1);
}

static int	add_path_to_cmd_name(char **cmd)
{
	char	*cmd_name;
	char	*path_variable;

	if (!cmd[0] || (!is_path_defined(&path_variable)))
		return (0);
	cmd_name = get_absolute_path(cmd[0], path_variable);
	if (!cmd_name)
	{
		print_error("minishell: command not found.", 127);
		return (0);
	}
	free(cmd[0]);
	cmd[0] = cmd_name;
	return (1);
}

static void	execute_cmd(char **cmd)
{
	int		pid;
	int		status;
	char	**env;


	if (!cmd[0] || !add_path_to_cmd_name(cmd))
		return ;
	pid = fork();
	define_exec_signals();
	if (pid == 0)
	{
		env = array_env(&g_state);
		execve(cmd[0], cmd, env);
		free_split(env);
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
