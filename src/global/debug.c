/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:28:39 by numartin          #+#    #+#             */
/*   Updated: 2023/07/11 14:51:33 by numartin         ###   ########.fr       */
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
		"PIPE",
		"REDIR_IN",
		"REDIR_OUT",
		"REDIR_APPEND",
		"REDIR_FILE",
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

void	print_arr_str(char **arr, char *msg)
{
	int i;

	printf("DEBUG - %s\n", msg);
	i = 0;
	while(arr && arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
	printf("\n");
}
