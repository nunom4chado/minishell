/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:28:39 by numartin          #+#    #+#             */
/*   Updated: 2023/06/29 20:09:01 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_state *state)
{
	const char* token_types[] = {
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

	t_token *token = state->tokens;
	printf("\nDEBUG: (current tokens)\n");
	while (token)
	{
		printf(" - type: %s, data: %s\n", token_types[token->type], token->word);
		token = token->next;
	}
	printf("\n");
}
