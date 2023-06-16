/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:59:32 by numartin          #+#    #+#             */
/*   Updated: 2023/06/16 16:38:24 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
int parser(char *input, t_state *state)
{
    // if input has only spaces discard input and DON'T add to history
    if (ft_only_spaces(input))
    {
        free(input);
        return (1);
    }

    // TODO: maybe count must increase
    if(tokenizer(state, input))
    {
        add_history(input);
        clean_input(input, state);
        return (1);
    }

    // TODO: after tokenizer runs, if last token is | must join next command to it
    // prompt will change from minishell> to >
    if (incomplete_input(state))
    {
        if(reprompt(input, state))
            return (1);
    }

    print_tokens(state);
    print_heredocs(state);
    return (0);
}