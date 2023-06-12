/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:37:15 by numartin          #+#    #+#             */
/*   Updated: 2023/06/12 18:13:24 by numartin         ###   ########.fr       */
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
	state.words = NULL;

	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline("minishell$ ");
		add_history(input);
		if (handle_ctrl_d(input) || typed_exit(input))
			break ;
		state.cmd = ft_strdup(input);

		if(ft_split_quote(&state, input))
		{
			printf("error: unclosed quote\n");
			free(input);
			continue ;
		}
		free(input);


		t_word *lst = state.words;
		while (lst)
		{
			printf("%s\n", lst->word);
			free(lst->word);
			t_word *old = lst;
			lst = lst->next;
			free(old);
			state.words = NULL;
		}

		printf("---------------------\n");





		state.cmd = expand(&state);
		if (handle_builtin(&state, &count))
			continue ;

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
