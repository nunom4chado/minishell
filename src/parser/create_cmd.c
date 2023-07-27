/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:32:48 by numartin          #+#    #+#             */
/*   Updated: 2023/07/14 16:39:44 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_commands_length(t_token *current, t_token *pipe)
{
	int	i;

	i = 0;
	while (current != pipe)
	{
		if (current->type == WORD)
			i++;
		current = current->next;
	}
	return (i);
}

static char	**fill_command_array(t_token *current, t_token *end, char **cmd)
{
	int	i;

	i = 0;
	while (current != end)
	{
		if (current->type == WORD)
		{
			cmd[i] = ft_strdup(current->word);
			i++;
		}
		current = current->next;
	}
	return (cmd);
}

/**
 * Create an array with the command and the arguments until reaching the
 * end of the token list or the next pipe
*/
char	**create_command_array(t_token *token, t_token *pipe)
{
	char	**cmd;
	int		cmd_length;

	cmd_length = get_commands_length(token, pipe);
	cmd = (char **)malloc((cmd_length + 1) * sizeof(char *));
	cmd[cmd_length] = NULL;
	cmd = fill_command_array(token, pipe, cmd);
	return (cmd);
}
