/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:01:40 by numartin          #+#    #+#             */
/*   Updated: 2023/07/14 14:29:06 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_state		g_state;

/**
 * All signals must registered inside this function to keep them in on location
*/
void	register_signals(void)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * Pressing Ctr-c will print ^C after prompt and return a new, clean prompt
 *
 * @note Will always set exit status to 130.
*/
void	handle_ctrl_c(int signo)
{
	(void)signo;
	g_state.exit_status = CODE_CTR_C;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/**
 * Function to run when pressing ctr-c on main process
*/
int	handle_ctrl_d(char *cmd, t_state *state)
{
	(void)state;
	if (!cmd)
	{
		printf("exit\n");
		return (1);
	}
	return (0);
}

