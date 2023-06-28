/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodos-sa <jodos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 12:59:07 by jodos-sa          #+#    #+#             */
/*   Updated: 2023/06/28 15:49:27 by jodos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_state *state)
{
	t_export *lst = state->exp;
	while (lst)
	{
		if (lst->value == NULL)
			printf("%s%s\n", lst->dec, lst->key);
		else
			printf("%s%s=\"%s\"\n", lst->dec, lst->key, lst->value);
		lst = lst->next;
	}
}
t_export	*findexp(t_state *state, char *key)
{
	t_export	*find;

	find = state->exp;
	while(find != NULL)
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
	if (find != NULL)
	{
		free(find->value);
		find->value = ft_strdup(newvalue);
		return (0);
	}
	else //add if not existent
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
	while(find != NULL)
	{
		if (ft_strcmp(key, find->key) == 0)
		{
			return (find->value);
		}
		find = find->next;
	}
	return (NULL);
}