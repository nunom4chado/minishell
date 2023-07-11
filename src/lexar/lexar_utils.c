/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:52:47 by numartin          #+#    #+#             */
/*   Updated: 2023/07/11 14:51:36 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Extract a word to create a token. Return a pointer to the next char after
 * the current word
*/
char	*create_token(char *input, char *end, t_tk_type type, t_state *state)
{
	t_token		*node;
	char		*word;

	if (*end)
	{
		word = ft_substr(input, 0, end - input + 1);
		node = lst_token_new(word, type);
		lst_token_add_back(&state->tokens, node);
		return (end + 1);
	}
	return (end);
}

/**
 * Iterate over string until null byte.
 * If the char at position 0 is found, the number of steps will be returned.
 * Return -1 if has no next occurrence.
*/
int	steps_next_occurrence(char *input)
{
	int	steps;

	steps = 1;
	while (input[steps])
	{
		if (input[steps] == input[0])
			return (steps);
		steps++;
	}
	return (-1);
}

/**
 * Determine if the current char is a metachar and returns it.
 *
 * @note special characters are ['|', '>', '>>', '<', '<<']
 *
 * @return char * of the current meta character
 * @return empty char * if there are no metachars at the current position
*/
char	*get_meta_characters(char *input)
{
	if (*input == '|')
		return ("|");
	if (*input == '>')
	{
		if (*(input + 1) == '>')
			return (">>");
		return (">");
	}
	if (*input == '<')
	{
		if (*(input + 1) == '<')
			return ("<<");
		return ("<");
	}
	return ("");
}

/**
 * Split on special characters
 *
 * chars: <, <<, >, >>, |
 *
*/
char	*ft_split_specialchar(char *input, t_state *state)
{
	if (validate_token_sequence(input, state))
	{
		ft_putstr_fd("syntax error near unexpected token ", 2);
		ft_putendl_fd(get_meta_characters(input), 2);
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
 *
 * TODO: update exit status for all errors
*/
char	*handle_normal_token(char *input, t_state *state)
{
	int		i;
	t_token	*last;
	int		steps;

	i = 0;
	while (input[i] && !(ft_is_space(input[i]) || ft_is_specialchar(input[i])))
	{
		if (ft_is_quote(input[i]))
		{
			steps = steps_next_occurrence(input + i);
			if (steps == -1)
			{
				ft_putendl_fd("error unclosed quote", 2);
				state->exit_status = CODE_SYNTAX_ERROR;
				return (NULL);
			}
			i = i + steps;
		}
		i++;
	}
	last = lst_token_last(state->tokens);
	if (last && last->type == HEREDOC)
		return (create_token(input, input + i - 1, HEREDOC_DELIMITER, state));
	if (last && (last->type == REDIR_IN || last->type == REDIR_OUT || last->type == REDIR_APPEND))
		return (create_token(input, input + i - 1, REDIR_FILE, state));
	return (create_token(input, input + i - 1, WORD, state));
}

int	validate_last_token(t_state *state)
{
	t_token	*last;

	last = lst_token_last(state->tokens);
	if (ft_strcmp(last->word, "<") == 0 || ft_strcmp(last->word, "<<") == 0 || \
	ft_strcmp(last->word, ">") == 0 || ft_strcmp(last->word, ">>") == 0)
	{
		ft_putendl_fd("syntax error near unexpected token `newline'", 2);
		state->exit_status = CODE_SYNTAX_ERROR;
		return (1);
	}
	if (pending_pipe(state))
	{
		ft_putendl_fd("error: pending pipe", 2);
		state->exit_status = CODE_SYNTAX_ERROR;
		return (1);
	}
	return (0);
}

/**
 * Checks if the previous token is a special char
 * and can be used with the current token
 *
 * Valid: [prev, cur]
 * ["|", ">>"]
 * ["|", ">"]
 * ["|", "<"]
 * ["|", "<<"]
 *
 * First token CANNOT be a |
 *
 * Errors: [prev, cur]
 * [">>", ">"]
 * [">", ">"]
 * [">", ">>"]
 * ["<<", "<"]
 * ... any combination of these arrows
 * ["<", "|"]
 * ["<<", "|"]
 * [">", "|"]
 * [">>", "|"]
 * ["|", "|"]
*/
int	validate_token_sequence(char *input, t_state *state)
{
	t_token	*last;

	if (!state->tokens && *input == '|')
		return (1);
	last = lst_token_last(state->tokens);
	if (last && ft_is_specialchar(*(last->word)))
	{
		if (ft_is_redirect(*last->word) \
		&& (ft_is_redirect(*input) || *input == '|'))
			return (1);
		if (ft_is_redirect(*last->word) && ft_is_redirect(*input))
			return (1);
		if (*input == '|' && *last->word == '|')
			return (1);
	}
	return (0);
}

/**
 * Check if the last token is a pipe
 *
 * @return 1 if true
 * @return 0 if false
*/
int	pending_pipe(t_state *state)
{
	t_token	*last;

	last = lst_token_last(state->tokens);
	if ((last && *(last->word) == '|'))
		return (1);
	return (0);
}

/**
 * Checks if tokens have heredocs
 *
 * @return 1 if true
 * @return o if false
*/
int	has_heredocs(t_state *state)
{
	t_token	*token;

	if (!state->tokens)
		return (0);
	token = state->tokens;
	while (token)
	{
		if (token->type == HEREDOC)
			return (1);
		token = token->next;
	}
	return (0);
}
