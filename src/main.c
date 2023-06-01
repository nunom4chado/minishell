/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodos-sa <jodos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:37:15 by numartin          #+#    #+#             */
/*   Updated: 2023/05/19 14:25:57 by jodos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_ctrl_c(int signo)
{
	(void)signo;
	printf("\n");
	rl_replace_line("", rl_on_new_line());
	rl_redisplay();
}

int main(int argc, char **argv, char **envp)
{
	char *cmd;
	int count = 1;
	char **comands;
	int	i;
	int	x;
	int	fd;
	int	pipefd[2];
	
	(void)argc;
	(void)argv;
	fd = 1;
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		cmd = readline("minishell$ ");
		if (!cmd)
		{
			printf("exit\n");
			break;
		}
		if (strcmp (cmd, "exit") == 0)
			break;
		i = -1;
		x = -1;
		comands = ft_split(cmd, '|');
		while(comands[++i]);
		add_history(cmd);
		free(cmd);
		count++;
		while(++x < i - 1)
			open_cmd(pipefd, 0, comands[x], envp);
		last_cmd(pipefd, fd, comands[x], envp);
		wait(NULL);
	}
	rl_clear_history();
	free (cmd);
	return (EXIT_SUCCESS);
}


