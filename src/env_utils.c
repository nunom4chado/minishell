/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodos-sa <jodos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 13:47:07 by jodos-sa          #+#    #+#             */
/*   Updated: 2023/06/24 15:26:36 by jodos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_newenv(void *content)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (0);
	new_node->value = content;
	new_node->next = NULL;
	return (new_node);
}

t_env	*ft_envlast(t_env *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
			lst = lst->next;
		return (lst);
	}
	return (NULL);
}

void	ft_addenv_back(t_env **lst, t_env *new)
{
	t_env	*tail;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tail = ft_envlast(*lst);
	tail->next = new;
}

void	create_env(t_state *state, char **envi)
{
	char	*string;
	char	*key;
	char	*value;
	char	*deli;
	size_t	len;
	t_env	*newenv;
	int		i;

	i = -1;
	state->env = NULL;
	while (envi[++i] != NULL)
	{
		string = envi[i];
		deli = ft_strchr(string, '=');
		if (deli != NULL)
		{
			len = deli - string;
			key = malloc(len + 2);
			strncpy(key, string, ++len);
			key[len + 1] = '\0';
			value = ft_strdup(deli + 1);

			// Creating the new node for the env
			newenv = malloc(sizeof(t_env));
			newenv->key = key;
			newenv->value = value;
			newenv->next = NULL;

			// Insert the new node at the head
			ft_addenv_back(&state->env, newenv);
		}
	}
}
