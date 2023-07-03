/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodos-sa <jodos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 13:47:07 by jodos-sa          #+#    #+#             */
/*   Updated: 2023/06/29 16:21:25 by jodos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_newenv(void *key, void *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (0);
	new_node->key = key;
	new_node->value = value;
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
	t_env	*newenv;
	int		i;
	size_t	len;
	char	*key;
	char	*value;

	i = -1;
	state->env = NULL;
	while (envi[++i] != NULL)
	{
		if (ft_strchr(envi[i], '=') != NULL)
		{
			len = ft_strchr(envi[i], '=') - envi[i];
			key = malloc(len + 1);
			ft_memcpy(key, envi[i], len);
			key[len] = '\0';
			value = ft_strdup(ft_strchr(envi[i], '=') + 1);
			newenv = ft_newenv(key, value);
			ft_addenv_back(&state->env, newenv);
		}
	}
}
