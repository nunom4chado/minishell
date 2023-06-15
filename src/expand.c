/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:34:38 by numartin          #+#    #+#             */
/*   Updated: 2023/06/15 14:36:53 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand(char *cmd, int i, char *expand, int over)
{
	char	*total;

	total = malloc(ft_strlen(cmd) + ft_strlen(expand) - 1);
	ft_memcpy(total, cmd, i);
	total[i] = '\0';
	ft_strcat(total, expand);
	ft_strcat(total, cmd + i + 1 + over);
	free(cmd);
	return (total);
}

char	*ft_del_non_var(char *cmd, int i, int over)
{
	char	*total;

	total = malloc(ft_strlen(cmd) - over + i + 1);
	ft_memcpy(total, cmd, i);
	total[i] = '\0';
	ft_strcat(total, cmd + i + 1 + over);
	free(cmd);
	return (total);
}

/**
 * TODO: expand $? to the exit status of the most recent recently executed foreground pipeline
 * DON'T expand if enclosed with single quotes
*/
char	*expand(t_state *state)
{
	int i;
	char	*envari;

	i = 0;
	while (state->cmd[i])
	{
		if (state->cmd[i] == '~')
		{
			if (ft_getenv("HOME=", state))
			{
				state->cmd = ft_expand(state->cmd, i, ft_getenv("HOME=", state), 0);
				return(expand(state));
			}
		}
		if (state->cmd[i] == '$')
		{
			envari = ft_read_until(state->cmd + i + 1);
			if (ft_getenv(envari, state))
			{
				state->cmd = ft_expand(state->cmd, i, ft_getenv(envari, state), ft_strlen(envari) - 1);
				return(expand(state));
			}
			else
			{
				state->cmd = ft_del_non_var(state->cmd, i, ft_strlen(envari) - 1);
				return (expand(state));
			}
		}
		i++;
	}
	return (state->cmd);
}
