/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:06:49 by numartin          #+#    #+#             */
/*   Updated: 2023/06/30 12:12:24 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_last_cmd(t_state *state)
{
	free(state->input);
	lst_token_clear(&(state->tokens), free);
}

void	clean_all(t_state *state)
{
	if (state->input)
		free(state->input);
	if (state->tokens)
		lst_token_clear(&(state->tokens), free);
	// TODO: clean env and export
}