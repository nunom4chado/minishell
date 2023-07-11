/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:37:15 by numartin          #+#    #+#             */
/*   Updated: 2023/07/11 11:36:14 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state		g_state;

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	init_state(&g_state);
	register_signals();
	create_env(&g_state, envp);
	create_exp(&g_state, envp);
	register_signals();

	while (1)
	{
		g_state.input = readline(prompt_style(&g_state));
		if (handle_ctrl_d(g_state.input, &g_state))
			break ;
		if (process_input(&g_state))
			continue ;

		if (is_builtin(g_state.cmd))
			execute_builtin(g_state.cmd, &g_state);
		else
		{
			last_cmd(&g_state);
			wait(NULL);
		}

		clean_last_cmd(&g_state);
	}
	rl_clear_history();
	clean_all(&g_state);
	return (EXIT_SUCCESS);
}
