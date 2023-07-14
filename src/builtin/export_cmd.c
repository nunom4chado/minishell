/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 13:33:23 by numartin          #+#    #+#             */
/*   Updated: 2023/07/14 13:35:28 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_state		g_state;

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