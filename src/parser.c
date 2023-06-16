/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:59:32 by numartin          #+#    #+#             */
/*   Updated: 2023/06/16 19:32:46 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pending_pipe(t_state *state)
{
    t_token *last;

	last = lst_last_token(state->tokens);
    if ((last && *(last->word) == '|'))
		return (1);
    return (0);
}

char    *prompt_style(t_state *state)
{
    if (pending_pipe(state) && state->heredocs)
        return ("pipe heredoc> ");
    if (state->heredocs)
        return ("heredoc> ");
    if (pending_pipe(state))
        return ("pipe> ");
    return ("> ");
}

int closed_heredoc(char *input, t_state *state)
{
    t_token *heredoc;

    state->heredocs = state->heredocs;
    if (state->heredocs)
    {
        if (ft_strcmp(state->heredocs->word, input) == 0)
        {
            // close heredoc
            heredoc = state->heredocs;
            state->heredocs = state->heredocs->next;
            free(heredoc);
            return (1);
        }
    }
    return (0);
}


/**
 * TODO: ctr-c must cancel reprompt
*/
int	reprompt(char *input, t_state *state)
{
	char *additional_input;
	char *tmp;

     print_heredocs(state);
	
	additional_input = readline(prompt_style(state));
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

    /**
     * If closed an heredoc reprompt
     * 
     * TODO: must refactor this!!
     * heredoc will accept input as is until closing word
     * This means not interpert pipes redirect and no expands
     * 
     * if not closing word just make additional_input a token and mark as no expand
    */
    if (closed_heredoc(additional_input, state))
    {
        free(additional_input);
        if (!state->heredocs)
            return (0);
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
	if (pending_pipe(state) || state->heredocs)
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
    if (pending_pipe(state) || state->heredocs)
    {
        if(reprompt(input, state))
            return (1);
    }

    print_tokens(state);
    print_heredocs(state);
    return (0);
}