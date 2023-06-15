/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:28:39 by numartin          #+#    #+#             */
/*   Updated: 2023/06/15 18:11:59 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_state *state)
{
	t_token *tokens = state->tokens;
	printf("---------------------\n");
	while (tokens)
	{
		printf("word: %s , space: %d\n", tokens->word, tokens->space);
		tokens = tokens->next;
	}
	printf("---------------------\n");
}