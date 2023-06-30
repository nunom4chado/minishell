/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:37:15 by numartin          #+#    #+#             */
/*   Updated: 2023/06/30 11:05:59 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state		g_state;

/**
 * Pressing Ctr-c will print ^C after prompt and return a new, clean prompt
 *
 * @note Will always set exit status to 130.
*/
void	handle_ctrl_c(int signo)
{
	(void)signo;

	//printf("debugging ctr-c 1\n");
	g_state.exit_status = CODE_CTR_C;

	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	int		count;

	count = 1;

	init_state(&g_state, envp);

	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);

	while (1)
	{
		g_state.input = readline(prompt_style(&g_state));

		if (handle_ctrl_d(g_state.input, &g_state) || typed_exit(g_state.input))
			break ;

		add_history(g_state.input);
		if (process_input(g_state.input, &g_state))
			continue ;


		//g_state.cmd = ft_strdup(input);
		//free(input);

/*

		if (handle_builtin(&g_state, &count))
			continue ;
*/

		/*
		if (fork1() == 0)
			runcmd(parseinput(input)); // parsecmd() and runcmd()
		*/

		// last_cmd(&g_state);
		// wait(NULL);
		lst_token_clear(&g_state.tokens, free);
		count++;
	}
	rl_clear_history();
	//free(g_state.cmd);
	return (EXIT_SUCCESS);
}
