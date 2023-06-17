/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:37:15 by numartin          #+#    #+#             */
/*   Updated: 2023/06/17 09:31:44 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **environ;

int	main()
{
	char	*input;
	int		count;
	t_state	state;

	count = 1;
	
	init_state(&state, environ);
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);

	while (1)
	{
		input = readline("minishell$ ");

		if (handle_ctrl_d(input) || typed_exit(input))
			break ;

		if (process_input(input, &state))
			continue ;

		//state.cmd = ft_strdup(input);
		//free(input);

		//state.cmd = expand(&state);
/*

		if (handle_builtin(&state, &count))
			continue ;
*/

		/*
		if (fork1() == 0)
			runcmd(parseinput(input)); // parsecmd() and runcmd()
		*/

		// last_cmd(&state);
		// wait(NULL);
		lst_token_clear(&state.tokens, free);
		count++;
	}
	rl_clear_history();
	//free(state.cmd);
	return (EXIT_SUCCESS);
}
