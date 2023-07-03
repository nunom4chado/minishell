/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodos-sa <jodos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 13:00:34 by jodos-sa          #+#    #+#             */
/*   Updated: 2023/07/01 14:28:06 by jodos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expdelone(t_export *lst)
{
	if (!lst)
		return ;
	free(lst);
}

void	ft_envdelone(t_env *lst)
{
	if (!lst)
		return ;
	free(lst);
}
