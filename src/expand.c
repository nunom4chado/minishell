/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:34:38 by numartin          #+#    #+#             */
/*   Updated: 2023/06/30 16:51:33 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_expanded_str(char *str, t_state *state)
{
	char	*new;
	char	quote_mode;
	char	*var_name;

	new = ft_calloc(1, 1);
	quote_mode = 0;
	while (*str)
	{
		if (toggle_quote_mode(*str, &quote_mode))
		{
			str++;
			continue ;
		}
		if (can_expand(str, quote_mode))
		{
			var_name = find_var_name(str + 1);
			new = append_var(new, var_name, state);
			str += 1 + ft_strlen(var_name);
			free(var_name);
			continue ;
		}
		new = append_char(new, *str);
		str++;
	}
	return (new);
}

void	expand_and_remove_quotes(t_token *token, t_state *state)
{
	char	*tmp;

	tmp = create_expanded_str(token->word, state);
	free(token->word);
	token->word = tmp;
}

/**
 * Remove quotes inside a token.
 *
 * @note It will remove only quotes that should be removed,
 * Eg. asdf"asd'sdf"sdf -> asdfasd'sdfsdf
*/
void	remove_quotes(t_token *token)
{
	char	*old;
	char	*new;
	char	quote_mode;

	old = token->word;
	new = ft_calloc(1, 1);
	quote_mode = 0;
	while (*old)
	{
		if (toggle_quote_mode(*old, &quote_mode))
		{
			old++;
			continue ;
		}
		new = append_char(new, *old);
		old++;
	}
	free(token->word);
	token->word = new;
}

/**
 * Apply variable expansions in token list
 *
 * @param state pointer to the state struct
 *
 * @note Expansions will not occur when the token is an HEREDOC_DELIMITER,
 * only quote removal will be applied
*/
void	expand(t_state *state)
{
	t_token	*token;

	token = state->tokens;
	while (token)
	{
		if (token->type == HEREDOC_DELIMITER)
			remove_quotes(token);
		else
		{
			ft_tilde_expand(token, state);
			expand_and_remove_quotes(token, state);
		}
		token = token->next;
	}
}
