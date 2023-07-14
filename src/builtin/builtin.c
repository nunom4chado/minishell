/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:17:17 by numartin          #+#    #+#             */
/*   Updated: 2023/07/14 13:39:01 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Execute a builtin command
*/
void	execute_builtin(char **cmd, t_state *state)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		builtin_echo(cmd + 1);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		builtin_cd(state, cmd + 1);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(cmd[0], "export") == 0)
	{
		if (cmd[1] == NULL)
			print_export(state);
		else
			builtin_export(state, cmd + 1);
	}
	else if (ft_strcmp(cmd[0], "unset") == 0)
		builtin_unset(state, cmd + 1);
	else if (ft_strcmp(cmd[0], "env") == 0)
	{
		if (cmd[1] == NULL)
			print_env(state);
	}
	else if (ft_strcmp(cmd[0], "exit") == 0)
		exit_builtin(cmd, state);
}
