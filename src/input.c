/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:59:32 by numartin          #+#    #+#             */
/*   Updated: 2023/07/03 17:21:54 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *prompt_style(t_state *state)
{
	(void)state;
	/*
	if (pending_pipe(state) && state->heredocs)
		return (PROMPT_PIPE_HEREDOC);
	if (pending_pipe(state))
		return (PROMPT_PIPE);
	if (state->heredocs)
		return (PROMPT_HEREDOC);
	*/
	return (PROMPT_DEFAULT);
}

/**
 * Process input will do lexical analysis which will split the input into a list
 * of tokens. Apply variable expansions and remove quotes. Lastly the parser
 * will create a list of the order of the execution of all the commands.
 *
 * @param state pointer to the state struct
 *
 * @return 0 when syntax is ok
 * @return 1 on syntax error or empty input
 *
 * TODO: check if the history command displays a list of previous commands
 * TODO: handle heredocs
*/
int process_input(t_state *state)
{
	if (!ft_strlen(state->input))
	{
		free(state->input);
		return (1);
	}

	add_history(state->input);
    if(lexar(state, state->input))
    {
        clean_last_cmd(state);
        return (1);
    }

    if (has_heredocs(state))
		ft_putendl_fd("\nTODO: handle heredocs\n", 2);

    //print_tokens(state);
    expand(state);
    //print_tokens(state);

	state->cmd = compose_cmd(state);

	//print_arr_str(state->cmd, "testing compose_cmd");

    return (0);
}
