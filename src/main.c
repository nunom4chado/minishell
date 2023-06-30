/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:37:15 by numartin          #+#    #+#             */
/*   Updated: 2023/06/30 14:11:11 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state		g_state;

/**
 * TODO: is count necessary??
*/
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	int		count;

	count = 1;
	init_state(&g_state, envp);
	register_signals();
	while (1)
	{
		g_state.input = readline(prompt_style(&g_state));
		if (handle_ctrl_d(g_state.input, &g_state) || typed_exit(&g_state))
			break ;
		if (process_input(&g_state))
			continue ;
		/*
		if (handle_builtin(&g_state, &count))
			continue ;

		if (fork1() == 0)
			runcmd(parseinput(input)); // parsecmd() and runcmd()

		last_cmd(&g_state);
		wait(NULL);
		*/
		clean_last_cmd(&g_state);
		count++;
	}
	rl_clear_history();
	clean_all(&g_state);
	return (EXIT_SUCCESS);
}
