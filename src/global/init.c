/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:08:02 by numartin          #+#    #+#             */
/*   Updated: 2023/07/25 14:53:38 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function responsible to initialize the state struct
 *
 * @param state pointer to the state struct
*/
void	init_state(t_state *state)
{
	state->env = NULL;
	state->exp = NULL;
	state->lastpid = 0;
	state->processes = 0;
	state->input = NULL;
	state->tokens = NULL;
}
