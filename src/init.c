/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:08:02 by numartin          #+#    #+#             */
/*   Updated: 2023/06/30 10:59:25 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_state(t_state *state, char **environ)
{
	state->envp = environ;
	state->input = NULL;
	state->tokens = NULL;
}
