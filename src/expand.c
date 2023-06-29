/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:34:38 by numartin          #+#    #+#             */
/*   Updated: 2023/06/29 17:26:39 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_and_remove_quotes(t_token *token, t_state *state)
{
	char *old;
	char *new;
	char quote;
	char *var_name;
	char *nb;
	char *tmp;

	old = token->word;
	new = ft_calloc(1, 1);
	quote = 0;
	while(*old)
	{
		// toggle quote and advance to next position
		if (ft_is_quote(*old))
		{
			if (quote == *old)
			{
				quote = 0;
				old++;
				continue ;
			}
			if (quote == 0)
			{
				quote = *old;
				old++;
				continue ;
			}
		}

		// Means it can expand the variable
		if (*old == '$' && *(old + 1) && !ft_is_quote(*(old + 1)) && quote != '\'')
		{
			var_name = find_var_name(old + 1);
			if (*var_name == '?')
			{
				nb = ft_itoa(state->exit_status);
				tmp = ft_strjoin(new, nb);
				free(new);
				free(nb);
				free(var_name);
				new = tmp;
				old += 2;
				continue ;
			}

			char *env_name = ft_strjoin(var_name, "=");
			if (ft_getenv(env_name, state))
			{
				tmp = ft_strjoin(new, ft_getenv(env_name, state));
				free(new);
				new = tmp;
			}

			old += 1 + ft_strlen(var_name);
			free(env_name);
			free(var_name);
			continue ;
		}

		// copy normal chars

		tmp = malloc(ft_strlen(new) + 2);
		ft_memcpy(tmp, new, ft_strlen(new));
		tmp[ft_strlen(new)] = *old;
		tmp[ft_strlen(new) + 1] = '\0';

		free(new);
		new = tmp;

		old++;
	}

	free(token->word);
	token->word = new;
}

/**
 * Remove quotes inside a token.
 *
 * @note It will remove only quotes that should be removed,
 * Eg. asdf"asd'sdf"sdf -> asdfasd'sdfsdf
*/
void	remove_quotes(t_token *token)
{
	char *old;
	char *new;
	char quote;
	char *tmp;

	old = token->word;
	new = ft_calloc(1, 1);
	quote = 0;
	while(*old)
	{
		// toggle quote and advance to next position
		if (ft_is_quote(*old))
		{
			if (quote == *old)
			{
				quote = 0;
				old++;
				continue ;
			}
			if (quote == 0)
			{
				quote = *old;
				old++;
				continue ;
			}
		}

		// copy normal chars
		tmp = malloc(ft_strlen(new) + 2);
		ft_memcpy(tmp, new, ft_strlen(new));
		tmp[ft_strlen(new)] = *old;
		tmp[ft_strlen(new) + 1] = '\0';

		free(new);
		new = tmp;

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
	t_token *token;

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
