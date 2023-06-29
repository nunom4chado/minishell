/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:52:47 by numartin          #+#    #+#             */
/*   Updated: 2023/06/29 19:59:58 by numartin         ###   ########.fr       */
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
		node = lst_new_token(word, type);
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
	int steps;

	steps = 1;
	while (input[steps])
	{
		if (input[steps] == input[0])
			return (steps);
		steps++;
	}
	return (-1);
}

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
		return (create_token(input, input, PIPE ,state));
	if (*input == '>')
	{
		if (*(input + 1) == '>')
			return (create_token(input, input + 1, REDIR_APPEND ,state));
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

char	*handle_normal_token(char *input, t_state *state)
{
	int		i;
	t_token	*last;
	int	steps;

	i = 0;
	while (input[i] && !(ft_is_space(input[i]) || ft_is_specialchar(input[i])))
	{
		if (ft_is_quote(input[i]))
		{
			steps = steps_next_occurrence(input + i);
			if (steps == -1)
			{
				ft_putendl_fd("error unclosed quote", 2);
				// TODO: update exit status for all errors
				return (NULL);
			}
			i = i + steps;
		}
		i++;
	}
	last = lst_last_token(state->tokens);
	if (last && last->type == HEREDOC)
		return(create_token(input, input + i - 1, HEREDOC_DELIMITER, state));
	return (create_token(input, input + i - 1, WORD, state));
}


int	validate_last_token(t_state *state)
{
	t_token	*last;

	last = lst_last_token(state->tokens);

	if (ft_strcmp(last->word, "<") == 0 || ft_strcmp(last->word, "<<") == 0 || \
	ft_strcmp(last->word, ">") == 0 || ft_strcmp(last->word, ">>") == 0)
	{
		ft_putendl_fd("syntax error near unexpected token `newline'", 2);
		return (1);
	}

	if (pending_pipe(state))
	{
		ft_putendl_fd("error: pending pipe", 2);
		return (1);
	}
	return (0);
}

/**
 * Must check if the previous token is a special char
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
	last = lst_last_token(state->tokens);
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