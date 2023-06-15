/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:37:15 by numartin          #+#    #+#             */
/*   Updated: 2023/06/15 13:09:09 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **environ;

int	incomplete_input(t_state *state)
{
	t_token *last;

	last = lst_last_token(state->tokens);

	if (last && *(last->word) == '|')
		return (1);
	/**
	 * TODO: heredoc must be checked here
	 * input: << o
	 * must add to input until the same word is entered 
	*/
	return (0);
}

int	main()
{
	char	*input;
	int		count;
	t_state	state;

	count = 1;
	state.envp = environ;
	state.tokens = NULL;

	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);

	while (1)
	{
		input = readline("minishell$ ");
		// TODO: history is in wrong place
		//add_history(input);

		if (handle_ctrl_d(input) || typed_exit(input))
			break ;

		// if input has errors tokenizer will return 1 and show another prompt
		// TODO: maybe count must increase
		if(tokenizer(&state, input))
		{
			add_history(input);
			clean_input(input, &state);
			continue ;
		}

		// TODO: after tokenizer if last token is | must join next command to it
		// prompt will change from minishell> to >
		if (incomplete_input(&state))
		{

			//reprompt(input, &state);
		}



		printf("---------------------\n");
		print_tokens(&state);
		printf("---------------------\n");

		state.cmd = ft_strdup(input);
		free(input);

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
	free(state.cmd);
	return (EXIT_SUCCESS);
}
