/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:28:10 by numartin          #+#    #+#             */
/*   Updated: 2023/07/26 11:55:41 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_last_input_fd(int old_pipe_in)
{
	if (old_pipe_in != 0)
		close(old_pipe_in);
}

/**
 * Restore the default standard output and input
*/
void	restore_std_fds(int *save_fd)
{
	dup2(save_fd[IN], STDIN_FILENO);
	close(save_fd[IN]);
	dup2(save_fd[OUT], STDOUT_FILENO);
	close(save_fd[OUT]);
}

/**
 * Dup the default file descriptors
*/
void	save_std_fds(int *save_fd)
{
	save_fd[IN] = dup(STDIN_FILENO);
	save_fd[OUT] = dup(STDOUT_FILENO);
}

void	eof_heap_to_stack(char *eof, char *delimiter)
{
	if (!eof)
		exit(EXIT_FAILURE);
	if (ft_strlen(eof) > 9999)
	{
		print_error("error: EOF too long", 1);
		free(eof);
		exit(EXIT_FAILURE);
	}
	ft_memset(delimiter, 0, 10000);
	ft_memmove(delimiter, eof, ft_strlen(eof));
	free(eof);
}
