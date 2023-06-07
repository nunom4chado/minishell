/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:34:38 by numartin          #+#    #+#             */
/*   Updated: 2023/06/07 16:05:08 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tilde_expand(char *cmd, int i, t_state *state)
{
	char *end;
	char *res;



	cmd[i] = '\0';
	end = (cmd + i + 1);
	printf("END Before %s\n", end);

	res = ft_strjoin(cmd, ft_getenv("HOME=", state));
	free(cmd);
	cmd = ft_strdup(res);
	free(res);

	if (*end)
	{
		printf("END %s\n", end);
		res = ft_strjoin(cmd, end);
		free(cmd);
		free(end);
		cmd = ft_strdup(res);
		free(res);
	}

	printf("%s\n", cmd);
}

char	*expand(char *cmd, t_state *state)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '~')
			ft_tilde_expand(cmd, i, state);
		i++;
	}
	return (cmd);
}
