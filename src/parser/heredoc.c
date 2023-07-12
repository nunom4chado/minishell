/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:04:32 by numartin          #+#    #+#             */
/*   Updated: 2023/07/12 19:03:51 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_state		g_state;

#define TMP_FILE	"/tmp/minishell_heredoc"


void	interrupt_here_document(int signal)
{
	(void)signal;
	g_state.exit_status = 130;
	write(1, "\n", 1);
	exit(130);
}

static int	create_temporary_file(void)
{
	int	fd;

	fd = open(TMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		print_error(strerror(errno), 1);
	return (fd);
}

static	void	get_and_write_input(int tmp_fd, char *eof)
{
	char	*input;

	signal(SIGINT, interrupt_here_document);
	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			print_error("warning: here-document delimited by end-of-file", 0);
			close(tmp_fd);
			exit(0);
		}
		if (ft_strcmp(input, eof))
			ft_putendl_fd(input, tmp_fd);
		else
		{
			close(tmp_fd);
			free(input);
			break ;
		}
		free(input);
	}
	exit(0);
}

static void	clear_tmp_file_input(void)
{
	int		tmp_fd;

	tmp_fd = open(TMP_FILE, O_WRONLY | O_TRUNC, 0600);
	close(tmp_fd);
}

static void	make_tmp_file_input(void)
{
	int		tmp_fd;

	tmp_fd = open(TMP_FILE, O_RDONLY);
	unlink(TMP_FILE);
	dup2(tmp_fd, IN);
	close(tmp_fd);
}

void	here_doc_input(char *eof, int *save_fd)
{
	int		tmp_fd;
	int		save_fd_out;
	int		pid;
	int		status;

	printf("handle heredoc with delimiter %s\n", eof);
	tmp_fd = create_temporary_file();
	if (tmp_fd == -1)
		return ;
	save_fd_out = dup(OUT);
	dup2(save_fd[OUT], STDOUT_FILENO);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		get_and_write_input(tmp_fd, eof);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		clear_tmp_file_input();
		g_state.exit_status = 130;
	}
	make_tmp_file_input();
	dup2(save_fd_out, STDOUT_FILENO);
	close(save_fd_out);
	printf("finish heredoc with delimiter %s\n", eof);
}
