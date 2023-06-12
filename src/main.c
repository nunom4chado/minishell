/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodos-sa <jodos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:37:15 by numartin          #+#    #+#             */
/*   Updated: 2023/06/12 15:32:07 by jodos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **environ;

int	main(int argc, char **argv)
{
	char	*input;
	int		count;
	t_state	state;


	errno = 0;
	count = 1;
	(void)argc;
	(void)argv;
	state.envp = environ;

	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline("minishell$ ");
		if (handle_ctrl_d(input) || typed_exit(input))
			break ;
		state.cmd = ft_strdup(input);
		add_history(input);
		free(input);
		state.cmd = expand(&state);
		if (state.cmd[0] == 'c' && state.cmd[1] == 'd' && (state.cmd[2] == ' ' || state.cmd[2] == '\0'))
		{
			cd_cmd(&state);
			count++;
			continue ;
		}

	/* 	if (fork1() == 0)
			runcmd(parseinput(input)); // parsecmd() and runcmd() */

		last_cmd(&state);
		wait(NULL);
		count++;
	}
	rl_clear_history();
	free(state.cmd);
	return (EXIT_SUCCESS);
}
