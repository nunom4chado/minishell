/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 13:26:10 by numartin          #+#    #+#             */
/*   Updated: 2023/07/14 13:28:04 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_state		g_state;

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