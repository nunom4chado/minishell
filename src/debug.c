/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:28:39 by numartin          #+#    #+#             */
/*   Updated: 2023/06/30 14:19:01 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Print the current tokens.
 * 
 * Tokens are created when the lexar runs.
*/
void	print_tokens(t_state *state)
{
	t_token		*token;
	const char	*token_types[] = {
		"WORD",
		"EXEC",
		"ARG",
		"PIPE",
		"REDIR_IN",
		"REDIR_OUT",
		"REDIR_APPEND",
		"HEREDOC",
		"HEREDOC_DELIMITER"
	};

	token = state->tokens;
	printf("\nDEBUG: (current tokens)\n");
	while (token)
	{
		printf(" - type: %s, data: %s\n", token_types[token->type], token->word);
		token = token->next;
	}
	printf("\n");
}
