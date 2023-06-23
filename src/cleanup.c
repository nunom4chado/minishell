/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:06:49 by numartin          #+#    #+#             */
/*   Updated: 2023/06/23 13:39:44 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_input(char *input, t_state *state)
{
	free(input);
	lst_token_clear(&(state->tokens), free);
	lst_token_clear(&state->heredocs, free);
}