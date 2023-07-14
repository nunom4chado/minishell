/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 13:35:53 by numartin          #+#    #+#             */
/*   Updated: 2023/07/14 13:42:43 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_state		g_state;

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
			continue ;
		len = 0;
		while (cmd[i][len] != '\0')
			len++;
		key = ft_substr(cmd[i], 0, len);
		unset_expvariables(state, key);
		unset_envvariables(state, key);
		free(key);
	}
	state->exit_status = 0;
}
