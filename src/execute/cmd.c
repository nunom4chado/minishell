/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:37:16 by jodos-sa          #+#    #+#             */
/*   Updated: 2023/07/11 15:43:48 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**array_env(t_state *state)
{
	int		num;
	int		i;
	t_env	*current;
	char	*string;
	char	**env;

	num = 0;
	current = state->env;
	while (current != NULL)
	{
		num++;
		current = current->next;
	}
	env = ft_calloc(sizeof(char **), num + 1);
	current = state->env;
	i = 0;
	while (current != NULL)
	{
		string = ft_strjoin(current->key, "=");
		env[i] = ft_strjoin(string, current->value);
		current = current->next;
		free(string);
		i++;
	}
	env[i] = NULL;
	return (env);
}

/* This one is the last cmd not the open cmd */
/*
void	last_cmd(t_state *state)
{
	char	**comand;
	pid_t	pid;
	int		pipefd[2];
	int		fd[2];

	fd[0] = 0;
	fd[1] = 0;
	array_env(state);
	pipe(pipefd);
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		comand = state->cmd;
		close(pipefd[1]);
		dup2(fd[1], STDOUT_FILENO);
		dup2(pipefd[0], STDIN_FILENO);
		if (comand[0] && path(comand[0], state->envp))
		{
			execve(path(comand[0], state->envp), comand, state->envp);
			//free_split(comand);
			exit(EXIT_SUCCESS);
		}
		state->exit_status = CODE_CMD_NOT_FOUND;
		printf("%s: command not found\n", comand[0]);
		//free_split(comand);
		exit(EXIT_FAILURE);
	}
	close(pipefd[0]);
	free_split(state->envp);
}
*/
