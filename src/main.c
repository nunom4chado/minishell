/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:37:15 by numartin          #+#    #+#             */
/*   Updated: 2023/05/16 17:33:06 by numartin         ###   ########.fr       */
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

void	handle_ctrl_slash(int signo, siginfo_t *info, void *context)
{
	(void)signo;
	(void)info;
	(void)context;

}

int main()
{

	struct sigaction	act;
	struct sigaction	act2;
	char *cmd;
	int count = 1;

	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &handle_ctrl_c;
	act2.sa_flags = SA_SIGINFO;
	act2.sa_sigaction = &handle_ctrl_slash;

	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act2, NULL);
	(void)cmd;

	while ((cmd = readline("minishell$ ")))
	{
		if (strcmp (cmd, "exit") == 0)
		{
			free (cmd);
			break;
		}
		add_history(cmd);
		free(cmd);
		count++;
	}

	return (EXIT_SUCCESS);
}


