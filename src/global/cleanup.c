/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:06:49 by numartin          #+#    #+#             */
/*   Updated: 2023/07/14 14:35:41 by numartin         ###   ########.fr       */
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
	state->input = NULL;
	lst_token_clear(&(state->tokens), free);
	state->tokens = NULL;
}

/**
 * Free all memory of the program.
 * Usefull to call before exiting the program
*/
void	clean_all(t_state *state)
{
	if (state->tokens)
		lst_token_clear(&(state->tokens), free);
	if (state->env)
		ft_delete_env(state->env);
	if (state->exp)
		ft_delete_export(state->exp);
	rl_clear_history();
}

/**
 * Free an array of strings
*/
void	free_split(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		i++;
	while (i > 0)
	{
		free(ptr[i - 1]);
		i--;
	}
	free(ptr);
}
