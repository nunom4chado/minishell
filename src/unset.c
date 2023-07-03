/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodos-sa <jodos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:31:08 by jodos-sa          #+#    #+#             */
/*   Updated: 2023/07/01 13:37:35 by jodos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_expvariables(t_state *state, char *key)
{
	t_export	*temp;
	t_export	*prev;

	temp = state->exp;
	prev = NULL;
	if (temp != NULL && temp->key == key)
	{
		state->exp = temp->next;
		ft_expdelone(temp);
		return ;
	}
	while (temp != NULL && ft_strcmp(temp->key, key) != 0)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return ;
	prev->next = temp->next;
	ft_expdelone(temp);
}

void	unset_envvariables(t_state *state, char *key)
{
	t_env	*temp;
	t_env	*prev;

	temp = state->env;
	prev = NULL;
	if (temp != NULL && temp->key == key)
	{
		state->env = temp->next;
		ft_envdelone(temp);
		return ;
	}
	while (temp != NULL && ft_strcmp(temp->key, key) != 0)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return ;
	prev->next = temp->next;
	ft_envdelone(temp);
}
