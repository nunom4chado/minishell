/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:09:14 by numartin          #+#    #+#             */
/*   Updated: 2023/06/15 15:47:28 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Last token can not be a redirect and first cannot be pipe '|'
*/
int	validate_last_token(t_state *state)
{
	t_token	*last;

	last = lst_last_token(state->tokens);
	if (ft_strcmp(last->word, "<") == 0 || ft_strcmp(last->word, "<<") == 0 || \
	ft_strcmp(last->word, ">") == 0 || ft_strcmp(last->word, ">>") == 0)
	{
		printf("syntax error near unexpected token `newline'\n");
		return (1);
	}
	if (state->tokens && *(state->tokens->word) == '|')
	{
		printf("syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}

/**
 * Must check if the previous token is a special char
 * and can be used with the current token
 * 
 * Valid: [perv, cur]
 * ["|", ">>"]
 * ["|", ">"]
 * 
 * Errors: [perv, cur]
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
