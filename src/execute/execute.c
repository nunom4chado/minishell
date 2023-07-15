/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:10:54 by numartin          #+#    #+#             */
/*   Updated: 2023/07/15 15:52:06 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_state		g_state;

/**
 * Create a char ** from env list
*/
char	**array_env(t_state *state)
{
	int		num;
	int		i;
	t_env	*current;
	char	**env;

	num = 0;
	current = state->env;
	while (current != NULL)
	{
		num++;
		current = current->next;
	}
	env = ft_calloc(sizeof(char **), num + 1);
	current = state->env;
	i = 0;
	while (current != NULL)
	{
		env[i] = join_three(current->key, "=", current->value);
		current = current->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

/**
 * Check if env has the variable PATH
*/
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

static int	valid_command_path(char **cmd, int *save_fd)
{
	char	*cmd_name;
	char	*path_variable;


	if (cmd[0] && (cmd[0][0] == '.' || cmd[0][0] == '/'))
		return (1);
	if (!cmd[0] || (!is_path_defined(&path_variable)))
		return (0);
	if (!is_executable(cmd[0]))
	{
		cmd_name = get_absolute_path(cmd[0], path_variable);
		if (!cmd_name)
		{
			restore_std_fds(save_fd);
			print_error("minishell: command not found.", 127);
			return (0);
		}
		free(cmd[0]);
		cmd[0] = cmd_name;
	}
	return (1);
}

static void	execute_cmd(char **cmd, int	*save_fd)
{
	//int		pid;
	char	**env;

	if (!cmd[0] || !valid_command_path(cmd, save_fd))
		return ;
	g_state.lastpid = fork();
	register_exec_signals();
	g_state.processes++;
	if (g_state.lastpid == 0)
	{
		env = array_env(&g_state);
		if (execve(cmd[0], cmd, env) == -1)
		{
			free_split(env);
			clean_all(&g_state);
			exit(127);
		}
	}
}

void	execute(char **cmd, int	*save_fd)
{
	int	i;

	i = 0;
	if (is_builtin(cmd))
		execute_builtin(&cmd[i], &g_state);
	else
		execute_cmd(&cmd[i], save_fd);
}
