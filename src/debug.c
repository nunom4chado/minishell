/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:28:39 by numartin          #+#    #+#             */
/*   Updated: 2023/06/23 15:51:21 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_state *state)
{
	const char* token_types[] = {
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
		printf(" - type: %s, word: %s\n", token_types[token->type], token->word);
		token = token->next;
	}
	printf("\n");
}

void	print_heredocs(t_state *state)
{
	t_token *heredoc = state->heredocs;
	printf("\nDEBUG: (current heredocs)\n");
	while (heredoc)
	{
		if (heredoc->word)
			printf("heredoc: %s\n", heredoc->word);
		heredoc = heredoc->next;
	}
	printf("\n");
}