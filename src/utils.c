/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:45:17 by jodos-sa          #+#    #+#             */
/*   Updated: 2023/06/14 18:59:53 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

int	ft_is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	ft_is_specialchar(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

char	*create_word(char *input, char *end, t_state *state)
{
	char	*word;
	t_word *node;
	int	space;

	space = 0;
	word = ft_substr(input, 0, end - input + 1);
	if (end && ft_is_space(*(end + 1)))
		space = 1;
	node = ft_new_word(word, space);
	ft_word_add_back(&state->words, node);
	return (end + 1);
}

char	*advance_quotes(char *input, char quote_type, t_state *state)
{
	char *matching_quote;

	matching_quote = ft_strchr(input + 1, quote_type);
	if(!matching_quote)
		return (NULL);
	input = create_word(input, matching_quote, state);
	return (input);
}

char *ft_split_quotes(t_state *state, char *input)
{
	if (*input == '\"')
		input = advance_quotes(input, '\"', state);
	if (*input == '\'')
		input = advance_quotes(input, '\'', state);
	return (input);
}


int	ft_split_words(t_state *state, char *input)
{
	int i;

	while(*input)
	{
		while (ft_is_space(*input))
			input++;
		if (*input == '\"' || *input == '\'')
		{
			input = ft_split_quotes(state, input);
			if (input == NULL)
				return (1);
			continue ;
		}
		i = 0;
		if (ft_is_specialchar(input[i]))
		(
			// must check if next is valid
			// >, >>, <, <<, |
			// errors: >>>, <<<, <<|, >>|, |||, ||
		)
		while(input[i] && !(ft_is_space(input[i]) || ft_is_quote(input[i]) || ft_is_specialchar(input[i])))
			i++;
		input = create_word(input, input + i - 1, state);
		printf("sadfadsf\n");
	}
	return (0);
}


void	free_split(char **args)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	while (args[size])
		size++;
	while (i < size)
		free(args[i++]);
	free(args);
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strcat(char *dest, char *src)
{
	int i;
	int j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	*ft_read_until(char *cmd)
{
	char	*str;
	int	i;
	int	x;

	i = 0;
	x = -1;
	if (!cmd)
		return (NULL);
	while (ft_isalnum(cmd[i]))
		i++;
	str = malloc(sizeof(char *) + i + 2);
	while (++x < i)
		str[x] = cmd[x];
	str[x] = '=';
	str[++x] = '\0';
	return (str);
}
