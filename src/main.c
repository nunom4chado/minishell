/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:37:15 by numartin          #+#    #+#             */
/*   Updated: 2023/06/16 14:27:54 by numartin         ###   ########.fr       */
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
	 * TODO: heredoc must be checked here or after this function runs
	 * input: << o
	 * must add to input until the same word is entered 
	*/
	return (0);
}


int	reprompt(char *input, t_state *state)
{
	char *additional_input;
	char *tmp;
	
	additional_input = readline("> ");
	handle_unexpected_eof(additional_input, input, state);
	
	/**
	 * Append to input
	 * TODO: if last was pipe, add a space in the middle
	 * TODO: for heredocs, add new line in the middle
	*/
	tmp = ft_strjoin(input, additional_input);
	free(input);
	input = tmp;

	if (ft_only_spaces(additional_input))
	{
		free(additional_input);
		return(reprompt(input, state));
	}

	// if reaches here means has content and its time to extract tokens
	if(tokenizer(state, additional_input))
	{
		add_history(input);
		clean_input(input, state);
		return (1);
	}
	// recursively call reprompt if not finished submitting input
	if (incomplete_input(state))
		return(reprompt(input, state));
	add_history(input);
	return (0);
}


/**
 * TODO: submitting new command from history must divide on newline when creating tokens
 * newlines '\n' will come from heredocs when added to history
*/
int	main()
{
	char	*input;
	int		count;
	t_state	state;

	count = 1;
	state.envp = environ;
	state.tokens = NULL;
	/**
	 * TODO: will be used to identify heredoc
	 * if the same heredoc is entered it will close the heredoc
	*/
	state.heredoc = NULL;

	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);

	while (1)
	{
		input = readline("minishell$ ");

		if (handle_ctrl_d(input) || typed_exit(input))
			break ;

		// if input has only spaces discard input and DON'T add to history
		if (ft_only_spaces(input))
		{
			free(input);
			continue ;
		}

		// TODO: maybe count must increase
		if(tokenizer(&state, input))
		{
			add_history(input);
			clean_input(input, &state);
			continue ;
		}

		// TODO: after tokenizer runs, if last token is | must join next command to it
		// prompt will change from minishell> to >
		if (incomplete_input(&state))
		{
			if(reprompt(input, &state))
				continue ;
		}

		print_tokens(&state);

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
