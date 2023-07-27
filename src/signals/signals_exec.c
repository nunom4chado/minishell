/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:28:34 by numartin          #+#    #+#             */
/*   Updated: 2023/07/25 14:45:15 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int		g_exit_status;

/**
 * Function to run when pressing ctrl-c on exec
*/
void	handle_exec_ctrl_c(int signal)
{
	(void)signal;
	g_exit_status = CODE_CTR_C;
	write(1, "\n", 1);
}

/**
 * Function to run when pressing ctrl-\ on exec
*/
static void	handle_exec_ctrl_bslash(int signal)
{
	(void)signal;
	g_exit_status = 131;
	printf("Quit (core dumped)\n");
}

/**
 * Signals inside exec
*/
void	register_exec_signals(void)
{
	signal(SIGINT, handle_exec_ctrl_c);
	signal(SIGQUIT, handle_exec_ctrl_bslash);
}
