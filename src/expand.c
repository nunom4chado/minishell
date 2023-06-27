/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:34:38 by numartin          #+#    #+#             */
/*   Updated: 2023/06/27 14:16:30 by numartin         ###   ########.fr       */
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
 * Expand variables and $? (previous exit status)
 * 
 * In this implementation, if the next character after '$' is not
 * '_', alpha char or '?', both the first and second chars will be
 * skipped and not saved
*/
void ft_variable_expand(t_token *token, t_state *state)
{
	char	*ptr;
	int		singlequote;

	singlequote = 0;
	ptr = token->word;

	/**
	 * $a = "Music Pictures"
	 * $b = " Music Pictures"
	 * $c = "Music Pictures "
	 * 
	 * $a"Videos" = ['Music', 'PicturesVideos']
	 * $a" Videos" = ['Music', 'Pictures Videos']
	 * $c"Videos" = ['Music', 'Pictures', 'Videos']
	 * $c" Videos" = ['Music', 'Pictures', ' Videos']
	 * "Videos"$b = ['Videos', 'Music', 'Pictures']
	 * "Videos "$b = [' Videos', 'Music', 'Pictures']
	 * "Videos"$a = ['VideosMusic', 'Pictures']
	 * "Videos "$a = ['Videos Music', 'Pictures']
	 * 
	 * $c"Videos"$c$a
	 * 
	 * "asdf $b sd"$b
	*/

	(void)state;
	(void)singlequote;

	while(*ptr)
	{

		if (*ptr == '$')
		{
			
		}
		ptr++;
	}
}

/**
 * In this implementation, if the next character after '$' is not
 * '_', alpha char or '?', both the first and second chars will be
 * skipped and not saved
*/
void	sanitize_invalid_variables(t_token *token)
{
	char *sanitized;
	char *aux;
	char *old;

	old = token->word;
	sanitized = malloc(ft_strlen(old) + 1);
	// TODO: handle error
	aux = sanitized;
	while (*old)
	{
		if (*old == '$' && *(old + 1))
		{
			if(!ft_isalpha(*(old + 1)) && *(old + 1) != '_' && *(old + 1) != '?')
			{
				old = old + 2;
				continue ;
			}
		}
		*aux = *old;
		aux++;
		old++;
	}
	*aux = '\0';
	free(token->word);
	token->word = sanitized;
}

// TODO: ft_remove_quotes();

void	expand(t_state *state)
{
	t_token *token;

	token = state->tokens;
	while (token)
	{
		// TODO only do this if token is not heredoc delimiter
		if (token->type != HEREDOC_DELIMITER)
		{
			ft_tilde_expand(token, state);
			sanitize_invalid_variables(token);
			//ft_variable_expand(token, state);
		}
		// ft_remove_quotes(token);
		// TODO: clear empty tokens
		token = token->next;
	}
}
