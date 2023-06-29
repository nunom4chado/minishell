/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodos-sa <jodos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:37:16 by jodos-sa          #+#    #+#             */
/*   Updated: 2023/06/29 16:22:08 by jodos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	array_env(t_state *state)
{
	int	num;
	int	i;
	t_env	*current;
	char	*string;

	num = 0;
	current = state->env;
	while (current != NULL)
	{
		num++;
		current = current->next;
	}
	state->envp = ft_calloc(sizeof(char **), num + 1);
	current = state->env;
	i = 0;
	while (current != NULL)
	{
		string = ft_strjoin(current->key, "=");
		state->envp[i] = ft_strjoin(string, current->value);
		current = current->next;
		i++;
	}
	state->envp[i] = NULL;
}

/* This one is the last cmd not the open cmd */
void	last_cmd(t_state *state)
{
	char	**comand;
	pid_t	pid;
	int	pipefd[2];
	int	fd[2];

	array_env(state);
	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
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
