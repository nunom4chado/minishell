/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:37:15 by numartin          #+#    #+#             */
/*   Updated: 2023/06/07 15:52:45 by numartin         ###   ########.fr       */
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
		expand(cmd, &state);
		if (cmd[0] == 'c' && cmd[1] == 'd')
		{
			cd_cmd(cmd, &state);
			continue ;
		}


	/* 	if (fork1() == 0)
			runcmd(parsecmd(cmd)); // parsecmd() and runcmd() */

		last_cmd(cmd, &state);
		wait(NULL);
		add_history(cmd);
		free(cmd);
		count++;
	}
	rl_clear_history();
	free(cmd);
	return (EXIT_SUCCESS);
}
