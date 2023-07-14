/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:37:45 by numartin          #+#    #+#             */
/*   Updated: 2023/07/14 15:51:32 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_three(char *one, char *two, char *three)
{
	char *tmp;
	char *final;

	if (!(one && two && three))
		return (NULL);
	tmp = ft_strjoin(one, two);
	final = ft_strjoin(tmp, three);
	free(tmp);
	return (final);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

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
