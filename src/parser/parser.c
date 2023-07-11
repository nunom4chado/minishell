/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:43:42 by numartin          #+#    #+#             */
/*   Updated: 2023/07/11 15:09:47 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_pipe(t_state *state)
{
	t_token	*token;

	token = state->tokens;
	while (token)
	{
		if (token->type == PIPE)
			return (1);
		token = token->next;
	}
	return (0);
}

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

static void	redirect_output(char *file, int flags)
{
	int	fd_file;

	fd_file = open(file, flags, 0777);
	if (fd_file == -1)
		print_error(strerror(errno), 1);
	else
	{
		dup2(fd_file, OUT);
		close(fd_file);
	}
}

static void	redirect_input(char *file, int flags)
{
	int	fd_file;

	fd_file = open(file, flags);
	if (fd_file == -1)
		print_error(strerror(errno), 1);
	else
	{
		dup2(fd_file, IN);
		close(fd_file);
	}
}

static void	make_redirect(char *redirect, char *file, int *save_fd)
{
	if (!ft_strcmp(redirect, ">"))
		redirect_output(file, O_WRONLY | O_CREAT | O_TRUNC);
	else if (!ft_strcmp(redirect, "<"))
		redirect_input(file, O_RDONLY | O_CREAT);
	else if (!ft_strcmp(redirect, ">>"))
		redirect_output(file, O_WRONLY | O_CREAT | O_APPEND);
	else if (!ft_strcmp(redirect, "<<"))
		here_doc_input(file, save_fd);
}

void	check_redirects(t_token *current, t_token *end, int *save_fd)
{
	while (current != end)
	{
		if (!current->next)
			break ;
		if (current->type == REDIR_IN || current->type == REDIR_OUT || current->type == REDIR_APPEND || current->type == HEREDOC)
		{
			make_redirect(current->word, current->next->word, save_fd);
			current = current->next;
		}
		current = current->next;
	}
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

static void	restore_std_fds(int *save_fd)
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
	execute(cmd);
	free_2d_array(cmd);
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
