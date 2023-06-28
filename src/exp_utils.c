/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodos-sa <jodos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:20:10 by jodos-sa          #+#    #+#             */
/*   Updated: 2023/06/28 15:41:49 by jodos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_export	*ft_newexp(void *key, void	*value)
{
	t_export	*new_node;
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (0);
	new_node->dec = ft_strdup("declare -x ");
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

/* t_export	*ft_explast(t_export *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
			lst = lst->next;
		return (lst);
	}
	return (NULL);
} */

/* void	ft_addexp_back(t_export **lst, t_export *new)
{
	t_export	*tail;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tail = ft_explast(*lst);
	tail->next = new;
} */

void	ft_addexp(t_export **lst, t_export *new)
{
	t_export	*current;

	if (*lst == NULL || ft_strcmp((*lst)->key, new->key) >= 0)
	{
		new->next = *lst;
		*lst = new;
	}
	else
	{
		current = *lst;
		while (current->next != NULL && ft_strcmp(current->next->key, new->key) < 0)
			current = current->next;
		new->next = current->next;
		current->next = new;
	}
}

// TODO: Make ft_strncpy 

void	create_exp(t_state *state, char **envi)
{
	char	*key;
	char	*value;
	size_t	len;
	t_export	*newexp;
	int		i;

	i = -1;
	state->exp = NULL;
	while (envi[++i] != NULL)
	{
		if (ft_strchr(envi[i], '=') != NULL)
		{
			len = ft_strchr(envi[i], '=') - envi[i];
			key = malloc(len + 2);
			strncpy(key, envi[i], len); 
			key[len + 1] = '\0';
			value = ft_strdup(ft_strchr(envi[i], '=') + 1);
			newexp = ft_newexp(key, value);
			ft_addexp(&state->exp, newexp);
		}
	}
}

