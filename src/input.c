/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:59:32 by numartin          #+#    #+#             */
/*   Updated: 2023/06/29 20:07:41 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *prompt_style(t_state *state)
{
	(void)state;
	/*
	if (pending_pipe(state) && state->heredocs)
		return (PROMPT_PIPE_HEREDOC);
	if (pending_pipe(state))
		return (PROMPT_PIPE);
	if (state->heredocs)
		return (PROMPT_HEREDOC);
	*/
	return (PROMPT_DEFAULT);
}

/**
 * Checks if tokens have heredocs
*/
int	has_heredocs(t_state *state)
{
	t_token *token;

	if (!state->tokens)
		return (0);
	token = state->tokens;
	while (token)
	{
		if (token->type == HEREDOC)
			return (1);
		token = token->next;
	}
    return (0);
}

/**
 * Check if the last token is a pipe
 * 
 * @return 1 if true
 * @return 0 if false
*/
int pending_pipe(t_state *state)
{
    t_token *last;

	last = lst_last_token(state->tokens);
    if ((last && *(last->word) == '|'))
		return (1);
    return (0);
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

    if (has_heredocs(state))
		ft_putendl_fd("\nTODO: handle heredocs\n", 2);

    print_tokens(state);
    expand(state);
    print_tokens(state);

    return (0);
}
