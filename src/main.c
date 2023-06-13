/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodos-sa <jodos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:37:15 by numartin          #+#    #+#             */
/*   Updated: 2023/06/13 17:49:40 by jodos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **environ;

int	main()
{
	char	*input;
	int		count;
	t_state	state;

	count = 1;
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

		if(ft_split_words(&state, input))
		{
			printf("error: unclosed quote\n");
			free(input);
			continue ;
		}
		free(input);


		t_word *lst = state.words;
		while (lst)
		{
			printf("word: %s > space: %d\n", lst->word, lst->space);
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
