/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:08:02 by numartin          #+#    #+#             */
/*   Updated: 2023/06/16 16:09:55 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    init_state(t_state *state, char **environ)
{
    state->envp = environ;
	state->tokens = NULL;
	/**
	 * TODO: will be used to identify heredocs
	 * if the same heredoc is entered it will close the heredoc
	*/
	state->heredocs = NULL;
}