/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:37:15 by numartin          #+#    #+#             */
/*   Updated: 2023/06/14 18:46:17 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **environ;

void	print_words(t_state *state)
{
	t_word *lst = state->words;
	while (lst)
	{
		printf("word: %s > space: %d\n", lst->word, lst->space);
		lst = lst->next;
	}
}

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

		if(ft_split_words(&state, input))
		{
			printf("error: unclosed quote\n");
			free(input);
			ft_wordclear(&state.words, free);
			continue ;
		}
		printf("---------------------\n");
		print_words(&state);
		printf("---------------------\n");

		state.cmd = ft_strdup(input);
		free(input);

		//state.cmd = expand(&state);
/*

		if (handle_builtin(&state, &count))
			continue ;
*/

		/*
		if (fork1() == 0)
			runcmd(parseinput(input)); // parsecmd() and runcmd()
		*/

		// last_cmd(&state);
		// wait(NULL);
		ft_wordclear(&state.words, free);
		count++;
	}
	rl_clear_history();
	free(state.cmd);
	return (EXIT_SUCCESS);
}
