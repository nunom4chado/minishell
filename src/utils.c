/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:45:17 by jodos-sa          #+#    #+#             */
/*   Updated: 2023/06/12 18:15:27 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_split_quote(t_state *state, char *input)
{
	char *matching_dquote;
	char *word;
	t_word *node;

	while(*input)
	{

		while (*input == ' ' || *input == '\t' || *input == '\v')
			input++;
		if (*input == '\"')
		{
			matching_dquote = ft_strchr(input + 1, '\"');
			if(!matching_dquote)
				return (1);
			word = ft_substr(input, 0, matching_dquote - input + 1);
			node = ft_new_word(word);
			ft_word_add_back(&state->words, node);
			input = matching_dquote + 1;
			continue ;
		}
		else if (*input == '\'')
		{
			matching_dquote = ft_strchr(input + 1, '\'');
			if(!matching_dquote)
				return (1);
			word = ft_substr(input, 0, matching_dquote - input + 1);
			node = ft_new_word(word);
			ft_word_add_back(&state->words, node);
			input = matching_dquote + 1;
			continue ;
		}
		else
		{
			int i = 0;
			while(input[i] && !(input[i] == ' ' || input[i] == '\t' || input[i] == '\v'))
				i++;
			word = ft_substr(input, 0, i);
			node = ft_new_word(word);
			ft_word_add_back(&(state->words), node);
			input = input + i + 1;
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
