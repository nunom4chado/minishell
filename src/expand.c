/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:34:38 by numartin          #+#    #+#             */
/*   Updated: 2023/06/26 21:07:10 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand(char *cmd, int i, char *expand, int over)
{
	char	*total;

	total = malloc(ft_strlen(cmd) + ft_strlen(expand) - 1);
	ft_memcpy(total, cmd, i);
	total[i] = '\0';
	ft_strcat(total, expand);
	ft_strcat(total, cmd + i + 1 + over);
	free(cmd);
	return (total);
}

char	*ft_del_non_var(char *cmd, int i, int over)
{
	char	*total;

	total = malloc(ft_strlen(cmd) - over + i + 1);
	ft_memcpy(total, cmd, i);
	total[i] = '\0';
	ft_strcat(total, cmd + i + 1 + over);
	free(cmd);
	return (total);
}


//int	is_var_key_valid(char *key)

/**
 * TODO: expand $? to the exit status of the most recent recently executed foreground pipeline
 * DON'T expand if enclosed with single quotes
 *
 * echo $7asdfsasdf   output: asdfsasdf
*/
/*
char	*expand(t_state *state)
{
	int i;
	char	*envari;

	i = 0;
	while (state->cmd[i])
	{
		if (state->cmd[i] == '~')
		{
			if (ft_getenv("HOME=", state))
			{
				state->cmd = ft_expand(state->cmd, i, ft_getenv("HOME=", state), 0);
				return(expand(state));
			}
		}
		if (state->cmd[i] == '$')
		{
			envari = ft_read_until(state->cmd + i + 1);
			if (ft_getenv(envari, state))
			{
				state->cmd = ft_expand(state->cmd, i, ft_getenv(envari, state), ft_strlen(envari) - 1);
				return(expand(state));
			}
			else
			{
				state->cmd = ft_del_non_var(state->cmd, i, ft_strlen(envari) - 1);
				return (expand(state));
			}
		}
		i++;
	}
	return (state->cmd);
}
*/

/**
 * Expand tilde in a token.
 * 
 * It will only expand if the first char is '~' and the second is '\0' or '/'
*/
void ft_tilde_expand(t_token *token, t_state *state)
{
	char	*tmp;

	if (token->word[0] == '~')
	{
		if (token->word[1] == '\0' || token->word[1] == '/')
		{
			tmp = ft_strjoin(ft_getenv("HOME=", state), token->word + 1);
			free(token->word);
			token->word = tmp;
		}
	}
}

/**
 * Expand variables and $? exit status
*/
void ft_variable_expand(t_token *token, t_state *state)
{
	char	*tmp;

	if (token->word[0] == '$')
	{
		(void)tmp;
		(void)state;
	}
}


//ft_remove_quotes();

void	expand(t_state *state)
{
	t_token *token;

	token = state->tokens;
	while (token)
	{
		ft_tilde_expand(token, state);
		ft_variable_expand(token, state);
		token = token->next;
	}
}
