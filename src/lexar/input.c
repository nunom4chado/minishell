/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:59:32 by numartin          #+#    #+#             */
/*   Updated: 2023/07/25 14:55:30 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int		g_exit_status;

/**
 * Process input will do lexical analysis which will split the input into a list
 * of tokens. Apply variable expansions and remove quotes. Lastly the parser
 * will create a list of the order of the execution of all the commands.
 *
 * @param state pointer to the state struct
 *
 * @return 0 when syntax is ok
 * @return 1 on syntax error or empty input
*/
int	process_input(t_state *state)
{
	if (!ft_strlen(state->input))
	{
		free(state->input);
		return (1);
	}
	add_history(state->input);
	if (lexar(state, state->input))
	{
		g_exit_status = CODE_SYNTAX_ERROR;
		clean_last_cmd(state);
		return (1);
	}
	expand(state);
	parse_and_execute(state);
	return (0);
}
