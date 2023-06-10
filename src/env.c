/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodos-sa <jodos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:26:43 by numartin          #+#    #+#             */
/*   Updated: 2023/06/10 15:17:42 by jodos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_setenv(char *key, char *newvalue, t_state *state)
{
	int i;
	char *res;

	i = 0;
	while(state->envp[i])
	{
		if (ft_strncmp(key, state->envp[i], ft_strlen(key)) == 0)
		{
			res = ft_strjoin(key, newvalue);
			state->envp[i] = ft_strdup(res);
			free(res);
			return (0);
		}
		i++;
	}

	return (-1);
}

char	*ft_getenv(char *key, t_state *state)
{
	int i;

	i = 0;
	while(state->envp[i])
	{
		if (ft_strncmp(key, state->envp[i], ft_strlen(key)) == 0)
			return(state->envp[i] + ft_strlen(key));
		i++;
	}
	return (NULL);
}
