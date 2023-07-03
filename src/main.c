/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodos-sa <jodos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:37:15 by numartin          #+#    #+#             */
/*   Updated: 2023/06/26 15:07:42 by jodos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **environ;

void	print_words(t_state *state)
{
	t_env *lst = state->env;
	while (lst)
	{
		printf("word: %s=%s\n", lst->key, lst->value);
		lst = lst->next;
	}
}

int	main()
{
	char	*input;
	int		count;
	t_state	state;

	count = 1;
	create_env(&state, environ);
	create_exp(&state, environ);
	
	/* printf("---------------------\n");
	print_words(&state);
	printf("---------------------\n"); */


	//state.envp = environ;
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

		state.cmd = ft_strdup(input);
		free(input);

		state.cmd = expand(&state);


		if (handle_builtin(&state, &count))
			continue ;


		/*
		if (fork1() == 0)
			runcmd(parseinput(input)); // parsecmd() and runcmd()
		*/

		last_cmd(&state);
		wait(NULL);
		ft_wordclear(&state.words, free);
		count++;
	}
	rl_clear_history();
	free(state.cmd);
	return (EXIT_SUCCESS);
}
