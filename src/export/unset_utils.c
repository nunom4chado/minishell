/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 13:00:34 by jodos-sa          #+#    #+#             */
/*   Updated: 2023/07/07 18:18:20 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expdelone(t_export *lst)
{
	if (!lst)
		return ;
	free(lst->dec);
	free(lst->key);
	free(lst->value);
	free(lst);
}

void	ft_delete_export(t_export *lst)
{
	t_export *tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		ft_expdelone(tmp);
	}
}

void	ft_envdelone(t_env *lst)
{
	if (!lst)
		return ;
	free(lst->key);
	free(lst->value);
	free(lst);
}

void	ft_delete_env(t_env *lst)
{
	t_env *tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		ft_envdelone(tmp);
	}
}
