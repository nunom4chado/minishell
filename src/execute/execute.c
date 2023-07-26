/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:10:54 by numartin          #+#    #+#             */
/*   Updated: 2023/07/26 11:16:13 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
static int	is_path_defined(char **path_variable, t_state *state)
{
	t_env	*path;

	path = findenv(state, "PATH");
	if (!path)
	{
		print_error("no such file or directory.", 127);
		return (0);
	}
	*path_variable = path->value;
	return (1);
}

static int	valid_command_path(char **cmd, int *save_fd, t_state *state)
{
	char	*cmd_name;
	char	*path_variable;

	if (cmd[0] && (cmd[0][0] == '.' || cmd[0][0] == '/'))
		return (1);
	if (!cmd[0] || (!is_path_defined(&path_variable, state)))
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

/**
 * Execute a command inside a child process
 *
 * @note Inside the children we must closed the copy of the default file
 * descriptors and the previous pipe in. Otherwise the child process will
 * have open fds and 'cat | cat | ls' will not work properly.
 *
 * @note In the main process we update the last pid because we want to wait
 * for that process to finish first.
*/
static void	execute_cmd(char **cmd, int	*save_fd, int *old_pipe_in,
	t_state *state)
{
	int		pid;
	char	**env;

	if (!cmd[0] || !valid_command_path(cmd, save_fd, state))
		return ;
	pid = fork();
	register_exec_signals();
	state->lastpid = pid;
	state->processes++;
	if (pid == 0)
	{
		close(save_fd[IN]);
		close(save_fd[OUT]);
		if (*old_pipe_in != 0)
			close(*old_pipe_in);
		env = array_env(state);
		if (execve(cmd[0], cmd, env) == -1)
			handle_execution_error(env, cmd, state);
	}
}

void	execute(char **cmd, int	*save_fd, int *old_pipe_in, t_state *state)
{
	int	i;

	i = 0;
	if (is_builtin(cmd))
		execute_builtin(&cmd[i], state);
	else
		execute_cmd(&cmd[i], save_fd, old_pipe_in, state);
}
