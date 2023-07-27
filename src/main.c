/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:37:15 by numartin          #+#    #+#             */
/*   Updated: 2023/07/25 14:58:35 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_exit_status;

void	wait_child_processes(t_state *state)
{
	int		status;

	if (waitpid(state->lastpid, &status, 0) != -1)
	{
		state->processes--;
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		state->lastpid = 0;
	}
	while (state->processes)
	{
		wait(0);
		state->processes--;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_state		state;

	(void)argc;
	(void)argv;
	init_state(&state);
	create_env(&state, envp);
	create_exp(&state, envp);
	while (1)
	{
		register_signals();
		state.input = readline(PROMPT_DEFAULT);
		if (handle_ctrl_d(state.input))
			break ;
		if (process_input(&state))
			continue ;
		wait_child_processes(&state);
		clean_last_cmd(&state);
	}
	clean_all(&state);
	return (EXIT_SUCCESS);
}
