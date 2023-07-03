/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:01:40 by numartin          #+#    #+#             */
/*   Updated: 2023/06/14 16:04:25 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_ctrl_c(int signo)
{
	(void)signo;
	printf("\n");
	rl_replace_line("", rl_on_new_line());
	rl_redisplay();
}

int	handle_ctrl_d(char *cmd)
{
	if (!cmd)
	{
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
