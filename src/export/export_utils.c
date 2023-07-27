/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:20:10 by jodos-sa          #+#    #+#             */
/*   Updated: 2023/07/14 14:50:53 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_export	*ft_newexp(void *key, void	*value)
{
	t_export	*new_node;

	new_node = malloc(sizeof(t_export));
	if (!new_node)
		return (0);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return (new_node);
}

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
		while (current->next != NULL
			&& ft_strcmp(current->next->key, new->key) < 0)
			current = current->next;
		new->next = current->next;
		current->next = new;
	}
}

void	create_exp(t_state *state, char **envi)
{
	char		*key;
	char		*value;
	int			len;
	t_export	*newexp;
	int			i;

	i = -1;
	state->exp = NULL;
	while (envi[++i] != NULL)
	{
		if (ft_strchr(envi[i], '=') != NULL)
		{
			len = ft_strchr(envi[i], '=') - envi[i];
			key = malloc(len + 1);
			ft_memcpy(key, envi[i], len);
			key[len] = '\0';
			value = ft_strdup(ft_strchr(envi[i], '=') + 1);
			newexp = ft_newexp(key, value);
			ft_addexp(&state->exp, newexp);
		}
		free(key);
		free(value);
	}
}
