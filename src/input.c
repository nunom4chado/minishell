/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:59:32 by numartin          #+#    #+#             */
/*   Updated: 2023/06/17 12:29:50 by numartin         ###   ########.fr       */
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

/**
 * Closes the current heredoc
*/
void close_heredoc(t_state *state)
{
    t_token *heredoc;

    if (state->heredocs)
    {
        heredoc = state->heredocs;
        state->heredocs = state->heredocs->next;
        free(heredoc);
    }
}

/**
 * Checks if word will close the current heredoc
 * 
 * Returns 1 if true, 0 otherwise
*/
int is_closing_word(char *word, t_state *state)
{
    if (state->heredocs)
    {
        if (ft_strcmp(state->heredocs->word, word) == 0)
            return (1);
    }
    return (0);
}

/**
 * Process current open heredoc.
 * 
 * Note: Heredoc content will not be inserted into state->tokens because
 * it will not be interpreted by execve or built-ins. We just need
 * to concat to previous input to create a correct history similar to bash.
 * 
 * Heredocs does not expand variables.
*/
char    *handle_heredoc(char *additional_input, char *input, t_state *state)
{
    char *tmp;
    
    //printf("before: %s$\n addinput: %s\n", input, additional_input);
    // concat additional_input to input separeted with a newline
    tmp = ft_strjoin(input, "\n");
	free(input);
	input = tmp;

    tmp = ft_strjoin(input, additional_input);
	free(input);
	input = tmp;
    //printf("after: %s$\n", input);

    if (is_closing_word(additional_input, state))
    {
        // when closing heredoc must add newline two
        tmp = ft_strjoin(input, "\n");
        free(input);
        input = tmp;
        close_heredoc(state);
    }
    free(additional_input);
    return (input);
}


/**
 * TODO: ctr-c must cancel reprompt
*/
char	*reprompt(char *input, t_state *state)
{
	char *additional_input;
	char *tmp;

	additional_input = readline(prompt_style(state));
	handle_unexpected_eof(additional_input, input, state);

    if (state->heredocs)
    {
        //print_heredocs(state);
        input = handle_heredoc(additional_input, input, state);
        return (input);
    }
	
    if (*additional_input)
    {
        tmp = ft_strjoin(input, additional_input);
        free(input);
        input = tmp;
    } 

    // TODO: check if lexar already handles this right
	if (ft_only_spaces(additional_input))
	{
		free(additional_input);
		return(reprompt(input, state));
	}

	// if reaches here means has pending pipe and its time to extract more tokens
	if(lexar(state, additional_input))
	{
		add_history(input);
		clean_input(input, state);
		return (NULL);
	}
    /**
     * TODO: if first char in input is space will not add to history
    */
	add_history(input);
	return (input);
}

/**
 * Process inserted input.
 * 
 * For blank chars, discard input;
 * Do lexical analysis;
 * If has pending pipe or heredocs means user can still enter subsquent inputs;
 * 
 * Return 1 on syntax error, 0 if successful.
 * 
 * TODO: submitting new command from history must divide on newline when creating tokens
 * newlines '\n' will come from heredocs when added to history
*/
int process_input(char *input, t_state *state)
{
    // if input has only spaces discard input and DON'T add to history
    if (ft_only_spaces(input))
    {
        free(input);
        return (1);
    }

    // TODO: maybe count must increase
    if(lexar(state, input))
    {
        add_history(input);
        clean_input(input, state);
        return (1);
    }

    // TODO: after lexar runs, if last token is | or has heredocs, must concat next input to previous
    while (pending_pipe(state) || state->heredocs)
    {
        input = reprompt(input, state);
        if(!input)
            return (1);
    }

    print_tokens(state);
    print_heredocs(state);
    return (0);
}