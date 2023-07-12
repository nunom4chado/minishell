/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodos-sa <jodos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:17:17 by numartin          #+#    #+#             */
/*   Updated: 2023/07/12 14:49:19 by jodos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_state		g_state;

/**
 * Exit the shell with status code saved on state and free all memory.
 *
 * @note exit will only work if has 0 arguments
*/
void	exit_builtin(char **cmd, t_state *state)
{
	int	len;

	len = -1;
	while (cmd[++len]);
	printf("exit\n");
	if (len > 2)
	{
		print_error("too many arguments", 1);
		return ;
	}
	if (len == 1)
		clean_all(state);
	if (len == 2)
	{
		if (ft_isnumber(cmd[1]))
		{
			clean_all(state);
			exit((char)ft_atoi(cmd[1]));
		}
		else
		{
			print_error("numeric argument required", 2);
			clean_all(state);
		}
	}
	exit(state->exit_status);
}

int	is_valid_key_unset(char *key, char *type)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(key[i]) || key[i] == '_'))
	{
		printf("minishell: %s: `%s': not a valid identifier\n", type, key);
		return (0);
	}
	i++;
	while (key[i] != '\0')
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_') || key[i] == '=' )
		{
			printf("minishell: %s: `%s': not a valid identifier\n", type, key);
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_valid_key(char *key, char *cmd, char *type)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(cmd[i]) || cmd[i] == '_'))
	{
		printf("minishell: %s: `%s': not a valid identifier\n", type, cmd);
		return (0);
	}
	i++;
	while (key[i] != '\0')
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
		{
			printf("minishell: %s: `%s': not a valid identifier\n", type, key);
			return (0);
		}
		i++;
	}
	return (1);
}

void	only_export(t_state *state, char *key)
{
	if (ft_getexp(key, state) == NULL)
		ft_setexp(key, NULL, state);
}

void	export_single(char *cmd, t_state *state)
{
	char	*key;
	char	*value;
	int		len;

	len = 0;
	while (cmd[len] != '\0' && cmd[len] != '=')
		len++;
	key = ft_substr(cmd, 0, len);
	if (!is_valid_key(key, cmd, "export"))
	{
		free(key);
		return ;
	}
	if (cmd[len] != '=')
	{
		only_export(state, key);
		free(key);
		return ;
	}
	value = ft_strdup(cmd + len + 1);
	ft_setenv(key, value, state);
	ft_setexp(key, value, state);
	free(key);
	free(value);
}

void	builtin_export(t_state *state, char **cmd)
{
	int	i;

	i = -1;
	if (has_pipe(state))
		return ;
	while (cmd[++i])
		export_single(cmd[i], state);
	g_state.exit_status = 0;
}

void	builtin_unset(t_state *state, char **cmd)
{
	char	*key;
	int		len;
	int		i;

	if (has_pipe(state))
		return ;
	i = -1;
	while (cmd[++i])
	{
		if (!is_valid_key_unset(cmd[i], "unset"))
			continue;
		len = 0;
		while (cmd[i][len] != '\0')
			len++;
		key = ft_substr(cmd[i], 0, len);
		unset_expvariables(state, key);
		unset_envvariables(state, key);
	}
	state->exit_status = 0;
}

void	builtin_echo(char **cmd)
{
	int	i;
	int	nl;

	if (g_state.echo)
	{
		i = 0;
		nl = 1;
		if (!cmd || !cmd[i])
		{
			printf("\n");
			return ;
		}
		while (ft_strcmp(cmd[i], "-n") == 0)
		{
			nl = 0;
			i++;
		}
		while (cmd[i])
		{
			printf("%s", cmd[i]);
			if (cmd [i + 1])
				printf(" ");
			i++;
		}
		if (nl)
			printf("\n");
		g_state.exit_status = 0;
	}
	g_state.echo = 1;
}

void	builtin_pwd()
{
	char	pwd[256];

	getcwd(pwd, sizeof(pwd));
	printf("%s\n", pwd);
	g_state.exit_status = 0;
}

void	execute_builtin(char **cmd, t_state *state)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		builtin_echo(cmd + 1);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		cd_cmd(state, cmd + 1);
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
