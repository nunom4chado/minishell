/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodos-sa <jodos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:37:16 by jodos-sa          #+#    #+#             */
/*   Updated: 2023/05/18 17:18:46 by jodos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_cmd(int *pipefd, int fd, char *cmd, char **envp)
{
	char	**comand;
	pid_t	pid;
	int	status;

	pipe(pipefd);
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		comand = ft_split(cmd, ' ');
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		if (comand[0] && path(comand[0], envp))
		{
			execve(path(comand[0], envp), comand, envp);
			free_split(comand);
			exit(EXIT_SUCCESS);
		}
		else if (fd)
			exit(EXIT_FAILURE);
		exit(EXIT_FAILURE);
	}
	close(pipefd[1]);
	//dup2(pipefd[0], STDIN_FILENO);
	waitpid(pid, &status, __W_CONTINUED);
}

/* This one is the last cmd not the open cmd */
void	last_cmd(int *pipefd, int fd, char *cmd, char **envp)
{
	char	**comand;
	pid_t	pid;
	int	status;

	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		comand = ft_split(cmd, ' ');
		close(pipefd[1]);
		dup2(fd, STDOUT_FILENO);
		dup2(pipefd[0], STDIN_FILENO);
		if (comand[0] && path(comand[0], envp))
		{
			execve(path(comand[0], envp), comand, envp);
			free_split(comand);
			exit(EXIT_SUCCESS);
		}
		exit(EXIT_FAILURE);
	}
	close(pipefd[0]);
	//dup2(pipefd[1], STDOUT_FILENO);
	waitpid(pid, &status, __W_CONTINUED);
}
