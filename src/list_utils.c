/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:30:01 by numartin          #+#    #+#             */
/*   Updated: 2023/06/16 13:45:50 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lst_new_token(void *word, int space)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (0);
	node->word = word;
	node->space = space;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_token	*lst_last_token(t_token *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
			lst = lst->next;
		return (lst);
	}
	return (NULL);
}

void	lst_token_add_back(t_token **lst, t_token *new)
{
	t_token	*tail;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tail = lst_last_token(*lst);
	tail->next = new;
	new->prev = tail;
}

void	lst_token_clear(t_token **lst, void (*del)(void *))
{
	t_token	*temp;
	t_token	*next_node;

	if (!lst || !del)
		return ;
	temp = *lst;
	while (temp != NULL)
	{
		next_node = temp->next;
		del(temp->word);
		free(temp);
		temp = next_node;
	}
	*lst = NULL;
}
