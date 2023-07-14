/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:34:38 by numartin          #+#    #+#             */
/*   Updated: 2023/07/14 12:15:12 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Toggle quote mode. When str[0] is a quote and quote mode is off (null-byte),
 * it sets the quote_mode to that type of quote. On later call, when it finds
 * the same quote type, it will set it back to null-byte
 *
 * @param str any char *
 * @param a pointer to the char to set the quote type
 *
 * @return 1 if toggle occurred
 * @return 0 otherwise
*/
int	toggle_quote_mode(const char c, char *quote_mode)
{
	if (ft_is_quote(c))
	{
		if (*quote_mode == c)
		{
			*quote_mode = 0;
			return (1);
		}
		if (*quote_mode == 0)
		{
			*quote_mode = c;
			return (1);
		}
	}
	return (0);
}

/**
 * Creates a new char * that will expand variables and remove quotes that
 * should be removed.
 *
 * @param str any char *
 * @param state pointer to state struct
 *
 * @return The resulting char *
*/
char	*expand_and_remove_quotes(char *str, t_state *state)
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
		if (can_expand(str, &quote_mode))
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
	char	*tmp;

	token = state->tokens;
	while (token)
	{
		if (token->type == HEREDOC_DELIMITER)
			remove_quotes(token);
		else
		{
			ft_tilde_expand(token, state);
			tmp = expand_and_remove_quotes(token->word, state);
			free(token->word);
			token->word = tmp;
		}
		token = token->next;
	}
}
