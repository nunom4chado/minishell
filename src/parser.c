/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodos-sa <jodos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:43:42 by numartin          #+#    #+#             */
/*   Updated: 2023/07/06 15:07:41 by jodos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_pipe(t_state *state)
{
	t_token	*token;

	token = state->tokens;
	while (token)
	{
		if (token->type == PIPE)
			return (1);
		token = token->next;
	}
	return (0);
}

char	**compose_cmd(t_state *state)
{
	char	**cmd;
	t_token	*token;
	int	len;
	int	i;

	len = lst_token_size(state->tokens);
	if (!len)
		return (NULL);
	cmd = malloc(sizeof(char *) * (len + 1));
	if (!cmd)
		return (NULL);
	token = state->tokens;
	i = 0;
	while(i < len)
	{
		cmd[i] = ft_strdup(token->word);
		token = token->next;
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}
