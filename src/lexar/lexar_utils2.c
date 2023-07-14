/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 12:11:15 by numartin          #+#    #+#             */
/*   Updated: 2023/07/14 16:27:43 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Checks if the previous token is a special char
 * and can be used with the current token
 *
 * Valid: [prev, cur]
 * ["|", ">>"]
 * ["|", ">"]
 * ["|", "<"]
 * ["|", "<<"]
 *
 * First token CANNOT be a |
 *
 * Errors: [prev, cur]
 * [">>", ">"]
 * [">", ">"]
 * [">", ">>"]
 * ["<<", "<"]
 * ... any combination of these arrows
 * ["<", "|"]
 * ["<<", "|"]
 * [">", "|"]
 * [">>", "|"]
 * ["|", "|"]
*/
int	validate_token_sequence(char *input, t_state *state)
{
	t_token	*last;

	if (!state->tokens && *input == '|')
		return (1);
	last = lst_token_last(state->tokens);
	if (last && ft_is_specialchar(*(last->word)))
	{
		if (ft_is_redirect(*last->word) \
		&& (ft_is_redirect(*input) || *input == '|'))
			return (1);
		if (ft_is_redirect(*last->word) && ft_is_redirect(*input))
			return (1);
		if (*input == '|' && *last->word == '|')
			return (1);
	}
	return (0);
}

/**
 * Check if the last token is a pipe
 *
 * @return 1 if true
 * @return 0 if false
*/
int	pending_pipe(t_state *state)
{
	t_token	*last;

	last = lst_token_last(state->tokens);
	if ((last && *(last->word) == '|'))
		return (1);
	return (0);
}

int	has_pipe(t_state *state)
{
	t_token	*token;

	token = state->tokens;
	while (token)
	{
		if (token->type == PIPE)
			return (1);
		token = token->next;
	}
	return (0);
}