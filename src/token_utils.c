/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:39:29 by numartin          #+#    #+#             */
/*   Updated: 2023/06/16 17:16:21 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_token(char *input, char *end, t_state *state)
{
	char	*word;
	t_token	*node;
	int		space;

	space = 0;
	if (*end)
	{
		word = ft_substr(input, 0, end - input + 1);
		if (end && ft_is_space(*(end + 1)))
			space = 1;
		node = lst_new_token(word, space);
		lst_token_add_back(&state->tokens, node);
		return (end + 1);
	}
	return (end);
}

void	create_heredoc(char *input, char *end, t_state *state)
{
	char	*word;
	t_token	*node;
	
	if (*end)
	{
		word = ft_substr(input, 0, end - input);
		node = lst_new_token(word, 0);
		lst_token_add_back(&state->heredocs, node);
	}
}

char	*advance_quotes(char *input, char quote_type, t_state *state)
{
	char	*matching_quote;

	matching_quote = ft_strchr(input + 1, quote_type);
	if (!matching_quote)
	{
		printf("error: unclosed quote\n");
		return (NULL);
	}
	input = create_token(input, matching_quote, state);
	return (input);
}

char	*ft_split_quotes(t_state *state, char *input)
{
	if (*input == '\"')
		input = advance_quotes(input, '\"', state);
	if (*input == '\'')
		input = advance_quotes(input, '\'', state);
	return (input);
}

/**
 * Split on special characters
 * 
 * chars: <, <<, >, >>, |
 * 
*/
char	*ft_split_specialchar(char *input, t_state *state)
{
	if (validate_token_sequence(input, state))
	{
		printf("syntax error near unexpected token `%c'\n", *input);
		return (NULL);
	}
	if (*input == '|')
		return (create_token(input, input, state));
	if (*input == '>')
	{
		if (*(input + 1) == '>')
			return (create_token(input, input + 1, state));
		else
			return (create_token(input, input, state));
	}
	if (*input == '<')
	{
		if (*(input + 1) == '<')
			return (create_token(input, input + 1, state));
		else
			return (create_token(input, input, state));
	}
	return (input);
}

char	*handle_normal_token(char *input, t_state *state)
{
	int		i;
	t_token	*last;

	i = 0;
	while (input[i] && !(ft_is_space(input[i]) || \
	ft_is_quote(input[i]) || ft_is_specialchar(input[i])))
		i++;
	last = lst_last_token(state->tokens);
	if (last && strcmp(last->word, "<<") == 0)
		create_heredoc(input, input + i, state);
	return (create_token(input, input + i - 1, state));
}
