/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:30:01 by numartin          #+#    #+#             */
/*   Updated: 2023/06/12 17:53:47 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_word	*ft_new_word(void *word)
{
	t_word	*node;

	node = malloc(sizeof(t_word));
	if (!node)
		return (0);
	node->word = word;
	node->next = NULL;
	return (node);
}

t_word	*ft_last_word(t_word *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
			lst = lst->next;
		return (lst);
	}
	return (NULL);
}

void	ft_word_add_back(t_word **lst, t_word *new)
{
	t_word	*tail;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tail = ft_last_word(*lst);
	tail->next = new;
}
