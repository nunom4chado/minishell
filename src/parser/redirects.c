/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:28:54 by numartin          #+#    #+#             */
/*   Updated: 2023/07/24 18:51:09 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_state		g_state;

static void	redirect_output(char *file, int flags)
{
	int	fd_file;

	fd_file = open(file, flags, 0644);
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
	{
		print_error(strerror(errno), 1);
		g_state.exit_status = 1;
	}
	else
	{
		dup2(fd_file, IN);
		close(fd_file);
	}
}

void	make_redirect(char *redirect, char *file, int *save_fd)
{
	if (!ft_strcmp(redirect, ">"))
		redirect_output(file, O_WRONLY | O_CREAT | O_TRUNC);
	else if (!ft_strcmp(redirect, "<"))
		redirect_input(file, O_RDONLY);
	else if (!ft_strcmp(redirect, ">>"))
		redirect_output(file, O_WRONLY | O_CREAT | O_APPEND);
	else if (!ft_strcmp(redirect, "<<"))
		heredoc(file, save_fd);
}

/**
 * Check if the current token is a redirect. If it is, perform the redirect
*/
void	check_redirects(t_token *current, t_token *end, int *save_fd)
{
	while (current != end)
	{
		if (!current->next)
			break ;
		if (current->type == REDIR_IN || current->type == REDIR_OUT || \
		current->type == REDIR_APPEND || current->type == HEREDOC)
		{
			make_redirect(current->word, current->next->word, save_fd);
			current = current->next;
		}
		current = current->next;
	}
}
