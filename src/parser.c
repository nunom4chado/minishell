/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:43:42 by numartin          #+#    #+#             */
/*   Updated: 2023/07/03 17:21:38 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



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
