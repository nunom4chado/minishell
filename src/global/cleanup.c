/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:06:49 by numartin          #+#    #+#             */
/*   Updated: 2023/07/03 17:27:20 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Free memory related to the last command. This is usefull
 * to call before the program prompts the user for more commands
*/
void	clean_last_cmd(t_state *state)
{
	free(state->input);
	lst_token_clear(&(state->tokens), free);
	clean_cmd(state->cmd);
}

/**
 * Free all memory of the program.
 * Usefull to call before exiting the program
 *
 * TODO: clean env and export inside this function
*/
void	clean_all(t_state *state)
{
	if (state->input)
		free(state->input);
	if (state->tokens)
		lst_token_clear(&(state->tokens), free);
}

void	clean_cmd(char **arr)
{
	while(arr && *arr)
	{
		free(*arr);
		arr++;
	}
}