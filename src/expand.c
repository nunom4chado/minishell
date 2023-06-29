/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:34:38 by numartin          #+#    #+#             */
/*   Updated: 2023/06/29 14:31:30 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/**
 * TODO: DON'T expand if enclosed with single quotes
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
		if (state->cmd[i] == '$')
		{
			envari = ft_read_until(state->cmd + i + 1);
			if (ft_getenv(envari, state))
			{
				state->cmd = ft_expand_var(state->cmd, i, ft_getenv(envari, state), ft_strlen(envari) - 1);
				return(expand(state));
			}
			else
			{
				state->cmd = skip_undefined_var(state->cmd, i, ft_strlen(envari) - 1);
				return (expand(state));
			}
		}
		i++;
	}
	return (state->cmd);
}
*/

char	*expand_inside_double_quotes(char *str, t_state *state)
{
	int	inside;
	int	i;
	char *name;
	char *nb;

	i = 0;
	inside = 0;

	while(str[i])
	{
		if (str[i] == '\"')
		{
			if (!inside)
				inside = 1;
			else
				inside = 0;
		}

		if (inside && str[i] == '$')
		{
			name = find_var_name(str + i + 1);
			if (*name == '?')
			{
				nb = ft_itoa(state->exit_status);
				str = ft_expand_var(str, i, nb, ft_strlen(name));
				free(nb);
				return(expand_inside_double_quotes(str, state));
			}

			char *envari = ft_strjoin(name, "=");
			if (ft_getenv(envari, state))
			{
				str = ft_expand_var(str, i, ft_getenv(envari, state), ft_strlen(name));
				free(envari);
				free(name);
				return(expand_inside_double_quotes(str, state));
			}
			else
			{
				str = skip_undefined_var(str, i, ft_strlen(name));
				free(name);
				free(envari);
				return (expand_inside_double_quotes(str, state));
			}
		}
		i++;
	}
	return (str);
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
	 * $c"Videos"$c$a = ['Music', 'Pictures', 'VideosMusic', 'Pictures', 'Music', 'Pictures']
	 * "asdf $b sd"$b = ['asdf Music Pictures sd', 'Music', 'Pictures']
	*/

	// First expand inside double quotes

	// expand outside quotes and handle dividing into new tokens
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

// TODO: ft_remove_quotes();



void	expand_and_remove_quotes(t_token *token, t_state *state)
{
	char *old;
	char *new;
	char quote;
	char *var_name;
	char *nb;
	char *tmp;

	old = token->word;
	new = ft_calloc(1, 1);
	quote = 0;
	while(*old)
	{
		// toggle quote and advance to next position
		if (ft_is_quote(*old))
		{
			if (quote == *old)
			{
				quote = 0;
				old++;
				continue ;
			}
			if (quote == 0)
			{
				quote = *old;
				old++;
				continue ;
			}
		}

		// Means it can expand the variable
		if (*old == '$' && *(old + 1) && !ft_is_quote(*(old + 1)) && quote != '\'')
		{
			var_name = find_var_name(old + 1);
			if (*var_name == '?')
			{
				nb = ft_itoa(state->exit_status);
				tmp = ft_strjoin(new, nb);
				free(new);
				free(nb);
				free(var_name);
				new = tmp;
				old += 2;
				continue ;
			}

			char *env_name = ft_strjoin(var_name, "=");
			if (ft_getenv(env_name, state))
			{
				tmp = ft_strjoin(new, ft_getenv(env_name, state));
				free(new);
				new = tmp;
			}

			old += 1 + ft_strlen(var_name);
			free(env_name);
			free(var_name);
			continue ;
		}

		// copy normal chars

		tmp = malloc(ft_strlen(new) + 2);
		ft_memcpy(tmp, new, ft_strlen(new));
		tmp[ft_strlen(new)] = *old;
		tmp[ft_strlen(new) + 1] = '\0';

		free(new);
		new = tmp;

		old++;
	}

	free(token->word);
	token->word = new;
}



/**
 * Expand tokens
 *
 * NOTE: expansions will not occur when the token is an HEREDOC_DELIMITER,
 * only quote removal will be applied
*/
void	expand(t_state *state)
{
	t_token *token;

	token = state->tokens;
	while (token)
	{
		if (token->type != HEREDOC_DELIMITER)
		{
			ft_tilde_expand(token, state);
			expand_and_remove_quotes(token, state);
		}
		// ft_remove_quotes(token);
		// TODO: clear empty tokens (some tokens may be left with only nullbyte - "")
		token = token->next;
	}
}
