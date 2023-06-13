/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodos-sa <jodos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:45:17 by jodos-sa          #+#    #+#             */
/*   Updated: 2023/06/13 16:17:13 by jodos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_word(char *input, char *end, t_state *state)
{
	char	*word;
	t_word *node;

	word = ft_substr(input, 0, end - input + 1);
	node = ft_new_word(word);
	ft_word_add_back(&state->words, node);
	//input = end + 1;
	return (end + 1);
}
/*
int	advance_quotes(char *input, char quote_type, t_state *state)
{
	char *matching_quote;

	matching_quote = ft_strchr(input + 1, quote_type);
	if(!matching_quote)
		return (1);
	input = create_word(input, matching_quote, state);
	return (0);
}
*/

int	ft_split_quote(t_state *state, char *input)
{
	char *matching_quote;

	while(*input)
	{
		while (*input == ' ' || *input == '\t' || *input == '\v')
			input++;
		if (*input == '\"')
		{
			matching_quote = ft_strchr(input + 1, '\"');
			if(!matching_quote)
				return (1);
			input = create_word(input, matching_quote, state);
			continue ;
		}
		else if (*input == '\'')
		{
			matching_quote = ft_strchr(input + 1, '\'');
			if(!matching_quote)
				return (1);
			input = create_word(input, matching_quote, state);
			continue ;
		}
		else
		{
			int i = 0;
			while(input[i] && !(input[i] == ' ' || input[i] == '\t' || input[i] == '\v'))
			{
				if (input[i] == '\"')
				{
					matching_quote = ft_strchr(input + i + 1, '\"');
					if(!matching_quote)
						return (1);
					i = matching_quote - input + i;
				}
				if (input[i] == '\'')
				{
					matching_quote = ft_strchr(input + i + 1, '\'');
					if(!matching_quote)
						return (1);
					i = matching_quote - input + i;
				}
				i++;
			}
			input = create_word(input, input + i, state);
		}
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
