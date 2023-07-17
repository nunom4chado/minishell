/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:37:15 by numartin          #+#    #+#             */
/*   Updated: 2023/07/17 20:26:32 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state		g_state;

int	main(int argc, char **argv, char **envp)
{
	int		status;
	(void)argc;
	(void)argv;
	init_state(&g_state);
	create_env(&g_state, envp);
	create_exp(&g_state, envp);
	//printf("PID: %d\n", getpid());
	while (1)
	{
		register_signals();
		g_state.input = readline(PROMPT_DEFAULT);
		if (handle_ctrl_d(g_state.input, &g_state))
			break ;
		if (process_input(&g_state))
			continue ;
		clean_last_cmd(&g_state);

		if (waitpid(g_state.lastpid, &status, 0) != -1)
		{
			//printf("waited LAST process\n");
			g_state.processes--;
			if (WIFEXITED(status))
				g_state.exit_status = WEXITSTATUS(status);
			g_state.lastpid = 0;
		}
		while (g_state.processes)
		{
			wait(0);
			//printf("waited 1 process\n");
			g_state.processes--;
		}
		//printf("END-- n of process in state %d\n", g_state.processes);

	}

	clean_all(&g_state);
	return (EXIT_SUCCESS);
}
