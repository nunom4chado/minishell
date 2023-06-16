/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:02:53 by numartin          #+#    #+#             */
/*   Updated: 2023/06/16 15:52:45 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Tokenizer is responsible for dividing the input stream
 * into individual tokens (words and special characters)
 * 
 * At the end will check the last token if is valid
 * return 0 if valid, 1 otherwise
*/

/**
 * If input ends with pipe or has heredoc in it:
 * 		- means input is not finished
 * 		- set in state why is incomplete (maybe a number? 1-pipe 2-heredoc 3-both)
 * 		- show new prompt (pipe heredoc>) (pipe>) (heredoc>)
*/
int	tokenizer(t_state *state, char *input)
{
	while (*input)
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
		input = handle_normal_token(input, state);
	}
	return (validate_tokens(state));
}
