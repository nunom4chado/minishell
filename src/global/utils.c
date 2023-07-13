/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:45:17 by jodos-sa          #+#    #+#             */
/*   Updated: 2023/07/13 17:50:54 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

int	ft_only_spaces(char *c)
{
	while (*c)
	{
		if (!ft_is_space(*c))
			return (0);
		c++;
	}
	return (1);
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

int	ft_is_redirect(char c)
{
	if (c == '<' || c == '>')
		return (1);
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

/**
 * Checks if the str is a valid number
 *
 * @param str string representing a number
 *
 * @note This function is used in exit.
 * @note -1 is valid number
 * @note -- if valid number
 * @note --- is not valid
 * @note --1 is not valid
 * @note -a is not valid
 *
 * @return 1 if true
 * @return 0 if false
*/
int	ft_isnumber(char *str)
{
	if (*str == '-')
	{
		str++;
		if (!*str)
			return (1);
		if (*str == '-' && *(str + 1) == '\0')
			return (1);
	}
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
