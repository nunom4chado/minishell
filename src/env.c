/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodos-sa <jodos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:26:43 by numartin          #+#    #+#             */
/*   Updated: 2023/07/01 13:50:22 by jodos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_state *state)
{
	t_env	*lst;

	lst = state->env;
	while (lst)
	{
		printf("word: %s%s\n", lst->key, lst->value);
		lst = lst->next;
	}
}

t_env	*findenv(t_state *state, char *key)
{
	t_env	*find;

	find = state->env;
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

int	ft_setenv(char *key, char *newvalue, t_state *state)
{
	t_env	*newenv;
	t_env	*find;

	find = findenv(state, key);
	if (find != NULL)
	{
		free(find->value);
		find->value = ft_strdup(newvalue);
		return (0);
	}
	else
	{
		newenv = ft_newenv(key, newvalue);
		ft_addenv_back(&state->env, newenv);
		return (0);
	}
	return (-1);
}

char	*ft_getenv(char *key, t_state *state)
{
	t_env	*find;

	find = state->env;
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
