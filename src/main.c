/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodos-sa <jodos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:37:15 by numartin          #+#    #+#             */
/*   Updated: 2023/05/17 18:19:43 by jodos-sa         ###   ########.fr       */
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
	
	(void)argc;
	(void)argv;
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
		last_cmd(cmd, envp);
		wait(NULL);
		add_history(cmd);
		free(cmd);
		count++;
		
	}
	rl_clear_history();
	free (cmd);
	return (EXIT_SUCCESS);
}


