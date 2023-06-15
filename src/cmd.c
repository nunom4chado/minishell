/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:37:16 by jodos-sa          #+#    #+#             */
/*   Updated: 2023/06/15 11:38:45 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



/* This one is the last cmd not the open cmd */
void	last_cmd(t_state *state)
{
	char	**comand;
	pid_t	pid;
	int	pipefd[2];
	int	fd[2];

	fd[0] = 0;
	fd[1] = 0;

	pipe(pipefd);
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		comand = ft_split(state->cmd, ' ');
		close(pipefd[1]);
		dup2(fd[1], STDOUT_FILENO);
		dup2(pipefd[0], STDIN_FILENO);
		if (comand[0] && path(comand[0], state->envp))
		{
			execve(path(comand[0], state->envp), comand, state->envp);
			free_split(comand);
			exit(EXIT_SUCCESS);
		}
		exit(EXIT_FAILURE);
	}
	close(pipefd[0]);
}
