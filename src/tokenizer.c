/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:02:53 by numartin          #+#    #+#             */
/*   Updated: 2023/06/15 11:45:48 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_token(char *input, char *end, t_state *state)
{
	char	*word;
	t_token *node;
	int	space;

	space = 0;
	word = ft_substr(input, 0, end - input + 1);
	if (end && ft_is_space(*(end + 1)))
		space = 1;
	node = lst_new_token(word, space);
	lst_token_add_back(&state->tokens, node);
	return (end + 1);
}

char	*advance_quotes(char *input, char quote_type, t_state *state)
{
	char *matching_quote;

	matching_quote = ft_strchr(input + 1, quote_type);
	if(!matching_quote)
	{
		handle_input_error("error: unclosed quote", input, state);
		return (NULL);
	}
	input = create_token(input, matching_quote, state);
	return (input);
}

char *ft_split_quotes(t_state *state, char *input)
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
 * Valid chars: <, <<, >, >>, |
 * 
 * If the previous token is also another special character
 * throw error because it will be a syntax error
 * 
 * Errors: >>>, <<<, <<|, >>|, |||, ||
*/
char	*ft_split_specialchar(char *input, t_state *state)
{
	t_token *last;
	
	last = lst_last_token(state->tokens);
	if (last && ft_is_specialchar(*(last->word)))
	{
		printf("syntax error near unexpected token\n");
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

/**
 * Tokenizer is responsible for dividing the input stream
 * into individual tokens (words and special characters)
*/
int	tokenizer(t_state *state, char *input)
{
	int i;

	while(*input)
	{
		while (ft_is_space(*input))
			input++;
		if (ft_is_quote(*input))
		{
			input = ft_split_quotes(state, input);
			if (input == NULL)
				return (1);
			continue ;
		}
		if (ft_is_specialchar(*input))
		{
			input = ft_split_specialchar(input, state);
			if (input == NULL)
				return (1);
			continue ;
		}
		i = 0;
		while(input[i] && !(ft_is_space(input[i]) || ft_is_quote(input[i]) || ft_is_specialchar(input[i])))
			i++;
		input = create_token(input, input + i - 1, state);
		//printf("sadfadsf\n");
	}
	return (0);
}