/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:28:54 by numartin          #+#    #+#             */
/*   Updated: 2023/07/25 14:43:32 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int		g_exit_status;

static int	redirect_output(char *file, int flags)
{
	int	fd_file;

	fd_file = open(file, flags, 0644);
	if (fd_file == -1)
	{
		print_error(strerror(errno), 1);
		g_exit_status = 1;
		return (1);
	}
	dup2(fd_file, OUT);
	close(fd_file);
	return (0);
}

/**
 * If file does not exist or an error ocurred must notify
 * parser to not execute the command in that section
 * (until reaching a pipe or end of the input)
*/
static int	redirect_input(char *file, int flags)
{
	int	fd_file;

	fd_file = open(file, flags);
	if (fd_file == -1)
	{
		print_error(strerror(errno), 1);
		g_exit_status = 1;
		return (1);
	}
	dup2(fd_file, IN);
	close(fd_file);
	return (0);
}

int	make_redirect(char *redirect, char *file, int *save_fd, t_state *state)
{
	int file_error;

	file_error = 0;
	if (!ft_strcmp(redirect, ">"))
		file_error = redirect_output(file, O_WRONLY | O_CREAT | O_TRUNC);
	else if (!ft_strcmp(redirect, "<"))
		file_error = redirect_input(file, O_RDONLY);
	else if (!ft_strcmp(redirect, ">>"))
		file_error = redirect_output(file, O_WRONLY | O_CREAT | O_APPEND);
	else if (!ft_strcmp(redirect, "<<"))
		file_error = heredoc(file, save_fd, state);
	return (file_error);
}

/**
 * Check if the current token is a redirect. If it is, perform the redirect
 * 
 * Notice that if inside a redirect an error occur we have to toggle file_error
 * to prevent the current command execution.
 * 
 * Also if a file error occur we can never set it back to 0. That's why if use it
 * inside an if statement.
*/
int	check_redirects(t_token *current, t_token *end, int *save_fd, t_state *state)
{
	int	file_error;

	file_error = 0;
	while (current != end)
	{
		if (!current->next)
			break ;
		if (current->type == REDIR_IN || current->type == REDIR_OUT || \
		current->type == REDIR_APPEND || current->type == HEREDOC)
		{
			if (make_redirect(current->word, current->next->word, save_fd, state))
				file_error = 1;
			current = current->next;
		}
		current = current->next;
	}
	return (file_error);
}
