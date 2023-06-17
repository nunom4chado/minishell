/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:28:39 by numartin          #+#    #+#             */
/*   Updated: 2023/06/17 09:54:19 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_state *state)
{
	t_token *tokens = state->tokens;
	printf("DEBUG: (current tokens)\n");
	while (tokens)
	{
		printf("word: %s, space: %d\n", tokens->word, tokens->space);
		tokens = tokens->next;
	}
	printf("<<<<<<<<<<<<<<<<<<<<<<<<<\n");
}

void	print_heredocs(t_state *state)
{
	t_token *heredoc = state->heredocs;
	printf("DEBUG: (current heredocs)\n");
	while (heredoc)
	{
		if (heredoc->word)
			printf("heredoc: %s\n", heredoc->word);
		heredoc = heredoc->next;
	}
	printf("<<<<<<<<<<<<<<<<<<<<<<<<<\n");
}