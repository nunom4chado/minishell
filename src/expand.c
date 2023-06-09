/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodos-sa <jodos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:34:38 by numartin          #+#    #+#             */
/*   Updated: 2023/06/09 17:43:38 by jodos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand(char *cmd, int i, char *expand)
{
	char	*total;

	total = malloc(ft_strlen(cmd) + ft_strlen(expand) - 1);
	ft_memcpy(total, cmd, i);
	total[i] = '\0';
	ft_strcat(total, expand);
	ft_strcat(total, cmd + i + 1);
	//printf("END: %s\n", total);
	free(cmd);
	return (total);
}

char	*expand(char *cmd, t_state *state)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '~')
		{
			cmd = ft_expand(cmd, i, ft_getenv("HOME=", state));
			i += ft_strlen(ft_getenv("HOME=", state)) - 1;
			return(expand(cmd, state));
		}
		i++;
	}
	return (cmd);
}
