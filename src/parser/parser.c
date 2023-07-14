/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:43:42 by numartin          #+#    #+#             */
/*   Updated: 2023/07/14 16:31:59 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_state		g_state;

char	**compose_cmd(t_state *state)
{
	char	**cmd;
	t_token	*token;
	int	len;
	int	i;

	len = lst_token_size(state->tokens);
	if (!len)
		return (NULL);
	cmd = malloc(sizeof(char *) * (len + 1));
	if (!cmd)
		return (NULL);
	token = state->tokens;
	i = 0;
	while(i < len)
	{
		cmd[i] = ft_strdup(token->word);
		token = token->next;
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}

static void	save_std_fds(int *save_fd)
{
	save_fd[IN] = dup(STDIN_FILENO);
	save_fd[OUT] = dup(STDOUT_FILENO);
}

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

void	restore_std_fds(int *save_fd)
{
	dup2(save_fd[IN], STDIN_FILENO);
	close(save_fd[IN]);
	dup2(save_fd[OUT], STDOUT_FILENO);
	close(save_fd[OUT]);
}

void	command_parser(t_token *token_lst, t_token *pipe, int *old_pipe_in)
{
	int		save_fd[2];
	char	**cmd;

	save_std_fds(save_fd);
	create_pipe(pipe, old_pipe_in);
	check_redirects(token_lst, pipe, save_fd);
	cmd = create_command_array(token_lst, pipe);
	//print_arr_str(cmd, "cmd and args");
	execute(cmd, save_fd);
	free_split(cmd);
	restore_std_fds(save_fd);
}

static void	pipe_checker(t_token *tokens, int *old_pipe_in)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == PIPE)
		{
			command_parser(tokens, current, old_pipe_in);
			tokens = current->next;
			pipe_checker(tokens, old_pipe_in);
			break ;
		}
		current = current->next;
	}
	if (!current)
		command_parser(tokens, current, old_pipe_in);
}

static void	close_last_input_fd(int old_pipe_in)
{
	if (old_pipe_in != 0)
		close(old_pipe_in);
}

void parse_and_execute(t_state *state)
{
	int	old_pipe_in;

	if (!state->tokens)
		return ;
	old_pipe_in = 0;
	pipe_checker(state->tokens, &old_pipe_in);
	close_last_input_fd(old_pipe_in);
}
