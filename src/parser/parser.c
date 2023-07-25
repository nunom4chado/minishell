/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:43:42 by numartin          #+#    #+#             */
/*   Updated: 2023/07/25 14:57:56 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Create a pipe to communicate between processes
 * 
 * @paragraph The previous pipe to STDIN
 * 
 * @paragraph If the previous pipe was diferent that 0, means its not the
 * original STDIN and we have to close it.
 * 
 * @paragraph if there is no pipe token means it's the last command and should
 * stop there.
 * 
 * @paragraph create the pipe
 * 
 * @paragraph make STDOUT reference the reading end of the pipe,
 * then close thatfd
 * 
 * @paragraph update the prev pipe in to point to the reading end of the pipe
*/
static void	create_pipe(t_token *pipe_token, int *old_pipe_in)
{
	int	new_pipe[2];

	dup2(*old_pipe_in, STDIN_FILENO);
	if (*old_pipe_in != STDIN_FILENO)
		close(*old_pipe_in);
	if (!pipe_token)
		return ;
	pipe(new_pipe);
	dup2(new_pipe[OUT], STDOUT_FILENO);
	close(new_pipe[OUT]);
	*old_pipe_in = new_pipe[IN];
}

/**
 * Parse a secion of tokens until pipe or end of list of tokens
*/
void	parse_command(t_token *token_lst, t_token *pipe, int *old_pipe_in, t_state *state)
{
	int		save_fd[2];
	char	**cmd;

	save_std_fds(save_fd);
	create_pipe(pipe, old_pipe_in);
	if (check_redirects(token_lst, pipe, save_fd, state) == 0)
	{
		cmd = create_command_array(token_lst, pipe);
		execute(cmd, save_fd, old_pipe_in, state);
		free_split(cmd);
	}
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
static void	parse_pipe(t_token *tokens, int *old_pipe_in, t_state *state)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == PIPE)
		{
			parse_command(tokens, current, old_pipe_in, state);
			tokens = current->next;
			parse_pipe(tokens, old_pipe_in, state);
			break ;
		}
		current = current->next;
	}
	if (!current)
		parse_command(tokens, current, old_pipe_in, state);
}

void	parse_and_execute(t_state *state)
{
	int	old_pipe_in;

	if (!state->tokens)
		return ;
	old_pipe_in = STDIN_FILENO;
	parse_pipe(state->tokens, &old_pipe_in, state);
	close_last_input_fd(old_pipe_in);
}
