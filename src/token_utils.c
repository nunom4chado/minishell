/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:39:29 by numartin          #+#    #+#             */
/*   Updated: 2023/06/26 14:56:59 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	create_heredoc(char *input, char *end, t_state *state)
{
	char	*word;
	t_token	*node;

	// TODO: bug here, last word if followed by null byte it does not add
	// removing the if check will give invalid read
	if (*end)
	{
		word = ft_substr(input, 0, end - input);
		node = lst_new_token(word, 0);
		lst_token_add_back(&state->heredocs, node);
	}
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
