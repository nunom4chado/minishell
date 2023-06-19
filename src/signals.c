/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:01:40 by numartin          #+#    #+#             */
/*   Updated: 2023/06/19 19:55:38 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_ctrl_d(char *cmd, t_state *state)
{
	if (!cmd)
	{
		if (state->heredocs || pending_pipe(state))
			printf("syntax error: unexpected end of file\nexit\n");
		else
			printf("exit\n");
		return (1);
	}
	return (0);
}

/**
 * TODO: memory leak, old cmd leaking
 * need to move to built-ins because of the following test
 *
 * export TEST=exit
 * $TEST
 *
 * should expand and exit the shell
*/
int	typed_exit(char *cmd)
{
	cmd = ft_strtrim(cmd, " \t\v");
	if (strcmp(cmd, "exit") == 0)
	{
		printf("exit\n");
		return (1);
	}
	return (0);
}
