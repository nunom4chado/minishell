/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 09:37:51 by numartin          #+#    #+#             */
/*   Updated: 2023/07/25 14:57:09 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int		g_exit_status;

/**
 * Create a token with a word or a token after a special token
*/
char	*handle_normal_token(char *input, t_state *state)
{
	int		i;
	t_token	*last;

	i = determine_token_len(input);
	if (i == -1)
		return (NULL);
	last = lst_token_last(state->tokens);
	if (last && last->type == HEREDOC)
		return (create_token(input, input + i - 1, HEREDOC_DELIMITER, state));
	if (last && (last->type == REDIR_IN || last->type == REDIR_OUT || \
	last->type == REDIR_APPEND))
		return (create_token(input, input + i - 1, REDIR_FILE, state));
	return (create_token(input, input + i - 1, WORD, state));
}

/**
 * Check what type of sepcial token we are dealing with
 *
 * chars: <, <<, >, >>, |
*/
char	*handle_special_token(char *input, t_state *state)
{
	if (validate_token_sequence(input, state))
	{
		ft_putstr_fd("syntax error near unexpected token ", 2);
		ft_putendl_fd(get_meta_characters(input), 2);
		g_exit_status = CODE_SYNTAX_ERROR;
		return (NULL);
	}
	if (*input == '|')
		return (create_token(input, input, PIPE, state));
	if (*input == '>')
	{
		if (*(input + 1) == '>')
			return (create_token(input, input + 1, REDIR_APPEND, state));
		else
			return (create_token(input, input, REDIR_OUT, state));
	}
	if (*input == '<')
	{
		if (*(input + 1) == '<')
			return (create_token(input, input + 1, HEREDOC, state));
		else
			return (create_token(input, input, REDIR_IN, state));
	}
	return (input);
}

/**
 * Lexar is responsible for dividing the input stream
 * into individual tokens (words and special characters)
 *
 * @param state pointer to state struct
 * @param input input from readline
 *
 * @return 0 on success
 * @return 1 if input has syntax errors
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
			input = handle_special_token(input, state);
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
