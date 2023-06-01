/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodos-sa <jodos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:37:15 by numartin          #+#    #+#             */
/*   Updated: 2023/06/01 16:22:18 by jodos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;
	int		count;

	count = 1;
	(void)argc;
	(void)argv;
	//(void)envp;
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		cmd = readline("minishell$ ");
		if (handle_ctrl_d(cmd) || typed_exit(cmd))
			break ;
		if (cmd[0] == 'c' && cmd[1] == 'd' && cmd[2] == ' ')
		{
			cd_cmd(cmd);
			continue ;
		}


	/* 	if (fork1() == 0)
			runcmd(parsecmd(cmd)); // parsecmd() and runcmd() */



		last_cmd(cmd, envp);
		wait(NULL);
		add_history(cmd);
		free(cmd);
		count++;
	}
	rl_clear_history();
	free(cmd);
	return (EXIT_SUCCESS);
}
