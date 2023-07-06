/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:17:17 by numartin          #+#    #+#             */
/*   Updated: 2023/07/06 12:07:56 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Exit the shell with status code saved on state and free all memory.
 * 
 * @note exit will only work if has 0 arguments
*/
void	exit_builtin(char **cmd, t_state *state)
{
	if (!cmd[1])
	{
		printf("exit\n");
		clean_all(state);
		exit(state->exit_status);
	}
}

int	is_valid_key(char *key)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(key[i]) || key[i] == '_'))
		return (0);
	i++;
	while (key[i] != '\0')
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_' || key[i] == '='))
			return (0);
		i++;
	}
	return (1);
}

int	only_export(t_state *state, char *key)
{
	char	*value;

	if (ft_getexp(key, state) == NULL)
	{
		value = NULL;
		ft_setexp(key, value, state);
		return (0);
	}
	return (1);
}

void	builtin_export(t_state *state)
{
	char	*line;
	char	*key;
	char	*value;
	int		len;

	len = 0;
	line = state->cmd[1];
	printf("arg %s\n", line);
	while (line[len] != '\0' && line[len] != '=')
		len++;
	key = ft_substr(line, 0, len);
	if (!is_valid_key(key))
	{
		printf("export: %s: not a valid identifier\n", line);
		free(key);
		free(line);
		return ;
	}
	if (line[len] != '=')
	{
		if (!only_export(state, key))
			return ;
	}
	value = ft_strdup(line + len + 1);
	ft_setenv(key, value, state);
	ft_setexp(key, value, state);
}

void	builtin_unset(t_state *state)
{
	char	*line;
	char	*key;
	int		len;

	len = 0;
	line = state->cmd[1];
	while (line[len] != '\0')
		len++;
	key = ft_substr(line, 0, len);
	unset_expvariables(state, key);
	unset_envvariables(state, key);
}

void	execute_builtin(char **cmd, t_state *state)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		printf("TODO: implement echo\n");
	else if (ft_strcmp(cmd[0], "cd") == 0)
		cd_cmd(state);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		printf("TODO: implemete pwd. MUST be an builtin and NOT use the bin pwd\n");
	else if (ft_strcmp(cmd[0], "export") == 0)
	{
		if (cmd[1] == NULL)
			print_export(state);
		else
			builtin_export(state);
	}
	else if (ft_strcmp(cmd[0], "unset") == 0)
		builtin_unset(state);
	else if (ft_strcmp(cmd[0], "env") == 0)
		printf("TODO: no env??\n");
	else if (ft_strcmp(cmd[0], "exit") == 0)
		exit_builtin(cmd, state);
}
