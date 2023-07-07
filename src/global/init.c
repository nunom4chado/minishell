/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodos-sa <jodos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:08:02 by numartin          #+#    #+#             */
/*   Updated: 2023/07/07 15:50:01 by jodos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function responsible to initialize the state struct
 *
 * @param state pointer to the state struct
 * @param envp from the main argument
*/
void	init_state(t_state *state, char **envp)
{
	state->envp = envp;
	state->input = NULL;
	state->tokens = NULL;
	state->cmd = NULL;
	state->exit_status = 0;
}
