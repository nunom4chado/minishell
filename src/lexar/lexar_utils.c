/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:52:47 by numartin          #+#    #+#             */
/*   Updated: 2023/07/25 14:55:55 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int		g_exit_status;

/**
 * Create a token. Return a pointer to the next char after
 * the current word
 * 
 * @param input pointer to string where the token will begin
 * @param end pointer to the end of the word
 * @param type type of the token
 * @param state global state
 * 
 * @return pointer to the next token
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
 * Will check the length of the current token
 * 
 * @param input pointer to current position we are checking
 * @param state global state
 * 
 * @return 0 or positive number on valid token
 * @return -1 when invalid
*/
int	determine_token_len(char *input)
{
	int		steps;
	int		i;

	steps = 0;
	i = 0;
	while (input[i] && !(ft_is_space(input[i]) || ft_is_specialchar(input[i])))
	{
		if (ft_is_quote(input[i]))
		{
			steps = steps_next_occurrence(input + i);
			if (steps == -1)
			{
				ft_putendl_fd("error unclosed quote", 2);
				g_exit_status = CODE_SYNTAX_ERROR;
				return (-1);
			}
			i = i + steps;
		}
		i++;
	}
	return (i);
}

int	validate_last_token(t_state *state)
{
	t_token	*last;

	last = lst_token_last(state->tokens);
	if (!last)
		return (1);
	if (ft_strcmp(last->word, "<") == 0 || ft_strcmp(last->word, "<<") == 0 || \
	ft_strcmp(last->word, ">") == 0 || ft_strcmp(last->word, ">>") == 0)
	{
		ft_putendl_fd("syntax error near unexpected token `newline'", 2);
		g_exit_status = CODE_SYNTAX_ERROR;
		return (1);
	}
	if (pending_pipe(state))
	{
		ft_putendl_fd("error: pending pipe", 2);
		g_exit_status = CODE_SYNTAX_ERROR;
		return (1);
	}
	return (0);
}
