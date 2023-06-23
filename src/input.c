/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:59:32 by numartin          #+#    #+#             */
/*   Updated: 2023/06/23 13:56:36 by numartin         ###   ########.fr       */
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

char *prompt_style(t_state *state)
{
	/*
	if (pending_pipe(state) && state->heredocs)
		return (PROMPT_PIPE_HEREDOC);
	if (pending_pipe(state))
		return (PROMPT_PIPE);
	*/
	if (state->heredocs)
		return (PROMPT_HEREDOC);
	return (PROMPT_DEFAULT);
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
void    handle_heredoc(char *input, t_state *state)
{
    if (is_closing_word(input, state))
        close_heredoc(state);
}

/**
 * Checks if tokens have heredocs
*/
int	has_heredoc(t_state * state)
{
    (void)state;
    return (1);
}

/**
 * Process inserted input.
 *
 * Do lexical analysis;
 * If has pending pipe or heredocs means user can still enter subsquent inputs;
 *
 * Return 1 on syntax error or incomplete input (heredocs, pending pipes), 0 if successful.
 * This will make reprompt until the user enter a complete, valid command
 *
 * TODO: make sure history it cannot build history if starts with space
*/
int process_input(char *input, t_state *state)
{
    if(lexar(state, input))
    {
        clean_input(input, state);
        return (1);
    }
    /*
    if (has_heredocs(state))
    {
		ft_putendl_fd("TODO: handle heredocs\n", 2);
        return (1);
    }
    */

    print_tokens(state);
    //print_heredocs(state);
    return (0);
}
