/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:17:17 by numartin          #+#    #+#             */
/*   Updated: 2023/06/14 18:33:26 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void	builtin_export(t_state *state)
{
	char	*path;
	char	*key;
	char	*value;

	path = ft_strtrim(state->cmd + 6, " \t\v");
	if (path && *path)
	{
		// path will be something like this "KEY=value"

		// ensure pattern is OK and has a value
		// extract key name
		// extract value
		ft_setenv(key, value, state);
	}

	// Does count increment if export failed? IDK
}
 */

int	is_valid_key(char *key)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(key[i]) || key[i] == '_'))
		return (0);
	while (key[++i] != '\0')
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
			return (0);
	}
	return (1);
}

/**
 * TODO: export without args must work
*/
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
	if (line[len] != '=')
		return ;
	key = ft_substr(line, 0, len + 1);
	if (!is_valid_key(key))
	{
		printf("export: %s: not a valid identifier\n", line);
		free(key);
		free(line);
		return ;
	}
	printf("KEY: %s\n", key);
	value = ft_strdup(line + len + 1);





	/* line = ft_strchr(line, '=');
	if (line[1] == ' ')
	{
		comand = malloc(len + ft_strlen(line) + 1);
		ft_memcpy(comand, line, len);
		ft_strcat(comand, " ");
	}
	else
	{
		comand = malloc(len + ft_strlen(line) + 1);
		ft_memcpy(comand, line, len);
		ft_strcat(comand, line);
	}
	i = -1;
	ft_setenv */
}

int	handle_builtin(t_state *state, int *count)
{
	char	**comand;

	comand = ft_split(state->cmd, ' ');
	if (ft_strcmp(comand[0], "cd") == 0)
	{
		cd_cmd(state);
		*count = *count + 1;
		return 1;
	}
	if (ft_strcmp(comand[0], "export") == 0)
	{
		builtin_export(state);
		*count = *count + 1;
		return 1;
	}
	return (0);
}
