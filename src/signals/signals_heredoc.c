/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:01:08 by numartin          #+#    #+#             */
/*   Updated: 2023/07/25 14:46:24 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int		g_exit_status;

void	handle_heredoc_ctrl_c(int signal)
{
	(void)signal;
	g_exit_status = 130;
	// TODO
	//clean_all(&g_state);
	write(1, "\n", 1);
	exit(130);
}
