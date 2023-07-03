/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodos-sa <jodos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:17:17 by numartin          #+#    #+#             */
/*   Updated: 2023/07/01 14:19:24 by jodos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	line = ft_strtrim(state->cmd + 6, " \t\v");
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
	line = ft_strtrim(state->cmd + 5, " \t\v");
	while (line[len] != '\0')
		len++;
	key = ft_substr(line, 0, len);
	unset_expvariables(state, key);
	unset_envvariables(state, key);
}

int	handle_builtin(t_state *state, int *count)
{
	char	**comand;

	comand = ft_split(state->cmd, ' ');
	if (ft_strcmp(comand[0], "cd") == 0)
	{
		cd_cmd(state);
		*count = *count + 1;
		return (1);
	}
	if (ft_strcmp(comand[0], "export") == 0)
	{
		if (comand[1] == NULL)
		{
			print_export(state);
			return (1);
		}
		builtin_export(state);
		*count = *count + 1;
		return (1);
	}
	if (ft_strcmp(comand[0], "unset") == 0)
	{
		builtin_unset(state);
		*count += 1;
		return (1);
	}
	return (0);
}
