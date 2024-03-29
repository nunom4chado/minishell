/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 12:59:07 by jodos-sa          #+#    #+#             */
/*   Updated: 2023/07/25 14:53:06 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int		g_exit_status;

void	print_export(t_state *state)
{
	t_export	*lst;

	lst = state->exp;
	while (lst)
	{
		if (lst->value == NULL)
			printf("declare -x %s\n", lst->key);
		else
			printf("declare -x %s=\"%s\"\n", lst->key, lst->value);
		lst = lst->next;
	}
	g_exit_status = 0;
}

t_export	*findexp(t_state *state, char *key)
{
	t_export	*find;

	find = state->exp;
	while (find != NULL)
	{
		if (ft_strcmp(key, find->key) == 0)
		{
			return (find);
		}
		find = find->next;
	}
	return (NULL);
}

int	ft_setexp(char *key, char *newvalue, t_state *state)
{
	t_export	*newexp;
	t_export	*find;

	find = findexp(state, key);
	if (find)
	{
		if (find->value != NULL)
			free(find->value);
		find->value = ft_strdup(newvalue);
		return (0);
	}
	else
	{
		newexp = ft_newexp(key, newvalue);
		ft_addexp(&state->exp, newexp);
		return (0);
	}
	return (-1);
}

char	*ft_getexp(char *key, t_state *state)
{
	t_export	*find;

	find = state->exp;
	while (find != NULL)
	{
		if (ft_strcmp(key, find->key) == 0)
		{
			return (find->value);
		}
		find = find->next;
	}
	return (NULL);
}
