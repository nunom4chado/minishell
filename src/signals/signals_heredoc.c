/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:01:08 by numartin          #+#    #+#             */
/*   Updated: 2023/07/27 15:19:57 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int		g_exit_status;

void	wait_and_update_main_signals(int pid, int *status)
{
	signal(SIGINT, SIG_IGN);
	waitpid(pid, status, 0);
	signal(SIGINT, handle_ctrl_c);
}

void	handle_heredoc_ctrl_c(int signal)
{
	(void)signal;
	g_exit_status = 130;
	write(1, "\n", 1);
	exit(130);
}
