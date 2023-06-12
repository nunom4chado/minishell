/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodos-sa <jodos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:34:38 by numartin          #+#    #+#             */
/*   Updated: 2023/06/12 15:00:56 by jodos-sa         ###   ########.fr       */
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

char	*expand(t_state *state)
{
	int i;
	char	*envari;

	i = 0;
	while (state->cmd[i])
	{
		if (state->cmd[i] == '~')
		{
			state->cmd = ft_expand(state->cmd, i, ft_getenv("HOME=", state), 0);
			i += ft_strlen(ft_getenv("HOME=", state)) - 1;
			return(expand(state));
		}
		if (state->cmd[i] == '$')
		{
			envari = ft_read_until(state->cmd + i + 1);
			state->cmd = ft_expand(state->cmd, i, ft_getenv(envari, state), ft_strlen(envari) - 1);
			i += ft_strlen(ft_getenv(envari, state)) - 1;
			return(expand(state));
		}
		i++;
	}
	return (state->cmd);
}
