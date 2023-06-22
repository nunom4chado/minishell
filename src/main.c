/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:37:15 by numartin          #+#    #+#             */
/*   Updated: 2023/06/22 16:20:09 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// #include <setjmp.h>
// sigjmp_buf mark;

extern char	**environ;

t_state		g_state;

/**
 * Pressing Ctr-c will print ^C after prompt a return a new, clean prompt
 *
 * If prompt is in pipe mode, or with heredocs open, must exit them and
 * display the normal prompt.
 *
 * Will always set exit status of 130.
 *
 * TODO: we must add to history is input is imcompleted
 * add inputed lines (this happens inputs ending with pipes or heredocs)
*/
void	handle_ctrl_c(int signo)
{
	(void)signo;

	printf("debugging ctr-c 1\n");
	g_state.exit_status = CODE_CTR_C;

	if (g_state.heredocs || pending_pipe(&g_state))
	{
		lst_token_clear(&g_state.tokens, free);
		lst_token_clear(&g_state.heredocs, free);
	}

	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();

}

int	main()
{
	int		count;

	count = 1;

	init_state(&g_state, environ);

	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);

	while (1)
	{
		g_state.input = readline(prompt_style(&g_state));

		if (handle_ctrl_d(g_state.input, &g_state) || typed_exit(g_state.input))
			break ;

		if (process_input(g_state.input, &g_state))
			continue ;

		//g_state.cmd = ft_strdup(input);
		//free(input);

		//g_state.cmd = expand(&g_state);
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
