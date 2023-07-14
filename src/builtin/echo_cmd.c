/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 13:26:10 by numartin          #+#    #+#             */
/*   Updated: 2023/07/14 14:14:16 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_state		g_state;

/**
 * Print a series of words separated by spaces.
 * Last word will NOT have a space.
 * 
 * At the end, if -n flag was set, don't print the newline
*/
void	print_words(char **word, int i, int nl_flag)
{
	while (word[i])
	{
		printf("%s", word[i]);
		if (word [i + 1])
			printf(" ");
		i++;
	}
	if (nl_flag)
		printf("\n");
}

/**
 * Execut builtin echo
 * 
 * @note -n flag is supported (will not print a newline at the end,
 * making the prompt appear in the same line)
*/
void	builtin_echo(char **cmd)
{
	int	i;
	int	nl_flag;

	if (g_state.echo)
	{
		i = 0;
		nl_flag = 1;
		if (!cmd || !cmd[i])
		{
			printf("\n");
			return ;
		}
		while (ft_strcmp(cmd[i], "-n") == 0)
		{
			nl_flag = 0;
			i++;
		}
		print_words(cmd, i, nl_flag);
		g_state.exit_status = 0;
	}
	g_state.echo = 1;
}
