/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numarrtin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:09:14 by numartin          #+#    #+#             */
/*   Updated: 2023/06/20 14:23:16 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_last_token(t_state *state)
{
	t_token	*last;

	last = lst_last_token(state->tokens);

	if (ft_strcmp(last->word, "<") == 0 || ft_strcmp(last->word, "<<") == 0 || \
	ft_strcmp(last->word, ">") == 0 || ft_strcmp(last->word, ">>") == 0)
	{
		ft_putendl_fd("syntax error near unexpected token `newline'", 2);
		return (1);
	}

	if (pending_pipe(state))
	{
		ft_putendl_fd("error: pending pipe", 2);
		return (1);
	}
	return (0);
}

/**
 * Must check if the previous token is a special char
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

	// first token cannot be a pipe '|'
	if (!state->tokens && *input == '|')
		return (1);
	last = lst_last_token(state->tokens);
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
