/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:37:15 by numartin          #+#    #+#             */
/*   Updated: 2023/07/14 12:16:30 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state		g_state;

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	init_state(&g_state);
	create_env(&g_state, envp);
	create_exp(&g_state, envp);
	while (1)
	{
		register_signals();
		g_state.input = readline(PROMPT_DEFAULT);
		if (handle_ctrl_d(g_state.input, &g_state))
			break ;
		if (process_input(&g_state))
			continue ;
		clean_last_cmd(&g_state);
	}
	clean_all(&g_state);
	return (EXIT_SUCCESS);
}
