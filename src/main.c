/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:37:15 by numartin          #+#    #+#             */
/*   Updated: 2023/05/17 15:04:05 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_ctrl_c(int signo, siginfo_t *info, void *context)
{
	printf("\n");
	(void)signo;
	(void)info;
	(void)context;
	rl_replace_line("", rl_on_new_line());
	rl_redisplay();
}

void	handle_ctrl_d(int signo, siginfo_t *info, void *context)
{
	(void)signo;
	(void)info;
	(void)context;

}

int main()
{

	struct sigaction	act;
	char *cmd;
	int count = 1;

	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &handle_ctrl_c;

	sigaction(SIGINT, &act, NULL);
	signal(SIGQUIT, SIG_IGN);
	(void)cmd;

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
		add_history(cmd);
		free(cmd);
		count++;
	}
	free (cmd);

	return (EXIT_SUCCESS);
}


