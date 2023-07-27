/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 19:43:18 by numartin          #+#    #+#             */
/*   Updated: 2023/07/25 19:52:17 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_all_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
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
	int	negative;

	negative = 0;
	if (ft_strlen(str) == 0)
		return (0);
	if (*str == '-')
	{
		str++;
		negative = 1;
	}
	if (!*str)
		return (0);
	if (*str == '-' && *(str + 1) == '\0')
		return (1);
	if (!is_all_digits(str))
		return (0);
	if (ft_strlen(str) > 19)
		return (0);
	if (!negative && ft_strcmp("9223372036854775807", str) < 0)
		return (0);
	if (negative && ft_strcmp("9223372036854775808", str) < 0)
		return (0);
	return (1);
}

long long	ft_atol(const char *str)
{
	long long	i;
	long long	sign;
	long long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	return (res * sign);
}
