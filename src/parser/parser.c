/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:43:42 by numartin          #+#    #+#             */
/*   Updated: 2023/07/14 16:55:15 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_state		g_state;

/**
 * Create a pipe to communicate between processes
*/
static void	create_pipe(t_token *pipe_token, int *old_pipe_in)
{
	int	new_pipe[2];

	dup2(*old_pipe_in, STDIN_FILENO);
	if (*old_pipe_in != 0)
		close(*old_pipe_in);
	if (!pipe_token)
		return ;
	pipe(new_pipe);
	dup2(new_pipe[OUT], STDOUT_FILENO);
	close(new_pipe[OUT]);
	*old_pipe_in = dup(new_pipe[IN]);
	close(new_pipe[IN]);
}

/**
 * Parse a secion of tokens until pipe or end of list of tokens
*/
void	parse_command(t_token *token_lst, t_token *pipe, int *old_pipe_in)
{
	int		save_fd[2];
	char	**cmd;

	save_std_fds(save_fd);
	create_pipe(pipe, old_pipe_in);
	check_redirects(token_lst, pipe, save_fd);
	cmd = create_command_array(token_lst, pipe);
	execute(cmd, save_fd);
	free_split(cmd);
	restore_std_fds(save_fd);
}

/**
 * check tokens until reaching a pipe.
 * 
 * @note If no pipes until the end, parse that section inside parse_command.
 * 
 * @note In case reaching a pipe, parse that section first, then recursively
 * call parse_pipe to handle other pipes
*/
static void	parse_pipe(t_token *tokens, int *old_pipe_in)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == PIPE)
		{
			parse_command(tokens, current, old_pipe_in);
			tokens = current->next;
			parse_pipe(tokens, old_pipe_in);
			break ;
		}
		current = current->next;
	}
	if (!current)
		parse_command(tokens, current, old_pipe_in);
}

void	parse_and_execute(t_state *state)
{
	int	old_pipe_in;

	if (!state->tokens)
		return ;
	old_pipe_in = 0;
	parse_pipe(state->tokens, &old_pipe_in);
	close_last_input_fd(old_pipe_in);
}
