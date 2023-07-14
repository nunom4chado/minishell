/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 19:55:01 by numartin          #+#    #+#             */
/*   Updated: 2023/07/14 12:13:37 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lst_token_new(void *word, t_tk_type type)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (0);
	node->type = type;
	node->word = word;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_token	*lst_token_last(t_token *lst)
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
	tail = lst_token_last(*lst);
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

int	lst_token_size(t_token *lst)
{
	int		i;
	t_token	*token;

	token = lst;
	i = 0;
	while (token)
	{
		i++;
		token = token->next;
	}
	return (i);
}
