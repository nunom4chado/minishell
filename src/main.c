/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:37:15 by numartin          #+#    #+#             */
/*   Updated: 2023/05/30 18:05:14 by numartin         ###   ########.fr       */
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
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		cmd = readline("minishell$ ");
		if (handle_ctrl_d(cmd) || typed_exit(cmd))
			break ;
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
