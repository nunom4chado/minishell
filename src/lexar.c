/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 09:37:51 by numartin          #+#    #+#             */
/*   Updated: 2023/06/23 15:53:36 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Lexar is responsible for dividing the input stream
 * into individual tokens (words and special characters)
 * 
 * At the end will check the last token if it is valid
 * return 0 if valid, 1 otherwise
*/
int	lexar(t_state *state, char *input)
{
	while (*input)
	{
		while (ft_is_space(*input))
			input++;
		if (*input == '\0')
			break ;
			
		if (ft_is_specialchar(*input))
		{
			input = ft_split_specialchar(input, state);
			if (input == NULL)
				return (1);
			continue ;
		}
		
		input = handle_normal_token(input, state);
		if (input == NULL)
			return (1);
	}
	return (validate_last_token(state));
}
