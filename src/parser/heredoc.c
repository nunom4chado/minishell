/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:04:32 by numartin          #+#    #+#             */
/*   Updated: 2023/07/27 15:19:47 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int		g_exit_status;

static int	create_temporary_file(void)
{
	int	fd;

	fd = open(HEREDOC_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		print_error(strerror(errno), 1);
	return (fd);
}

/**
 * Prompt the user to insert content and save it to tmp file
 *
 * @param tmp_fd file descriptor to the tmp file
 * @param eof heredoc delimiter
 *
 * @note will stop when reaching heredoc delimiter
*/
static	void	heredoc_input(int tmp_fd, char *eof, t_state *state)
{
	char	*input;
	char	delimiter[10000];

	clean_all(state);
	eof_heap_to_stack(eof, delimiter);
	signal(SIGINT, handle_heredoc_ctrl_c);
	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			print_error("warning: here-document delimited by end-of-file", 0);
			close(tmp_fd);
			exit(EXIT_SUCCESS);
		}
		if (ft_strcmp(input, delimiter) != 0)
			ft_putendl_fd(input, tmp_fd);
		else
			break ;
		free(input);
	}
	close(tmp_fd);
	free(input);
	exit(g_exit_status);
}

/**
 * Clean the content of the temporary file (beacause of O_TRUNC flag)
*/
static void	clear_tmp_file_input(void)
{
	int		tmp_fd;

	tmp_fd = open(HEREDOC_FILE, O_WRONLY | O_TRUNC, 0644);
	close(tmp_fd);
}

/**
 * Will make the heredoc file the input instead of the default input
*/
static void	update_input_fd(void)
{
	int		tmp_fd;

	tmp_fd = open(HEREDOC_FILE, O_RDONLY);
	unlink(HEREDOC_FILE);
	dup2(tmp_fd, STDIN_FILENO);
	close(tmp_fd);
}

/**
 * Handle heredoc. will prompt input until entered the delimiter word
 *
 * @param eof delimiter word
 * @param save_fd saved file descriptors
 *
 * @note This function will create a temporary file to store user input
 * and delete it when finished
*/
int	heredoc(char *eof, int *save_fd, t_state *state)
{
	int		tmp_fd;
	int		save_fd_out;
	int		pid;
	int		status;

	(void)state;
	tmp_fd = create_temporary_file();
	if (tmp_fd == -1)
		return (1);
	save_fd_out = dup(STDOUT_FILENO);
	dup2(save_fd[OUT], STDOUT_FILENO);
	dup2(save_fd[IN], STDIN_FILENO);
	pid = fork();
	if (pid == 0)
		heredoc_input(tmp_fd, ft_strdup(eof), state);
	wait_and_update_main_signals(pid, &status);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		clear_tmp_file_input();
		g_exit_status = 130;
	}
	update_input_fd();
	dup2(save_fd_out, STDOUT_FILENO);
	close(save_fd_out);
	return (0);
}
