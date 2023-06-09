/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodos-sa <jodos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:37:15 by numartin          #+#    #+#             */
/*   Updated: 2023/06/09 17:49:04 by jodos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **environ;

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;
	int		count;
	t_state	state;



	count = 1;
	(void)argc;
	(void)argv;
	(void)envp;
	state.envp = environ;

	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		cmd = readline("minishell$ ");
		if (handle_ctrl_d(cmd) || typed_exit(cmd))
			break ;
		add_history(cmd);
		cmd = expand(cmd, &state);
		//printf("END: %s\n", cmd);
		if (cmd[0] == 'c' && cmd[1] == 'd')
		{
			cd_cmd(cmd, &state);
			continue ;
		}


	/* 	if (fork1() == 0)
			runcmd(parsecmd(cmd)); // parsecmd() and runcmd() */

		last_cmd(cmd, &state);
		wait(NULL);
		free(cmd);
		count++;
	}
	rl_clear_history();
	free(cmd);
	return (EXIT_SUCCESS);
}
