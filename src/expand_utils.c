/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodos-sa <jodos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:38:22 by numartin          #+#    #+#             */
/*   Updated: 2023/07/05 15:58:15 by jodos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Find the full name of the variable
 *
 * @param str a pointer to the next character after the '$'
 *
 * @return char * with the name of the var
 *
 * @note If the variable has an invalid name, it will return the first char.
 * This is necessary to know the length to skip when iterating a string.
*/
char	*find_var_name(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '?')
		return (ft_substr(str, 0, 1));
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (ft_substr(str, 0, 1));
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (ft_substr(str, 0, i));
}

/**
 * Expand tilde '~' in a token.
 *
 * @note It will only expand if the first char is '~' and the
 * second is '\0' or '/'
 *
 * @param token pointer to the token to be expanded
 * @param state pointer to the program state struct
 * 
*/
void	ft_tilde_expand(t_token *token, t_state *state)
{
	char	*tmp;

	if (token->word[0] == '~')
	{
		if (token->word[1] == '\0' || token->word[1] == '/')
		{
			tmp = ft_strjoin(ft_getenv("HOME", state), token->word + 1);
			free(token->word);
			token->word = tmp;
		}
	}
}

/**
 * Determine if its possible to expand a variable in a char *.
 * 
 * @param str any char *
 * @param quote_mode a char to determine which mode the str should be consider
 * eg: single quote, double quote or none (null-byte)
 * 
 * @note str[0] must be '$'
 * @note str[0 + 1] cannot be '\0'
 * @note str[0 + 1] cannot be a quote
 * @note quote_mode cannot be single quote
 * 
 * @return 1 if true
 * @return 0 if false
*/
int	can_expand(const char *str, char quote_mode)
{
	if (*str == '$' && *(str + 1) && !ft_is_quote(*(str + 1))
		&& quote_mode != '\'')
		return (1);
	return (0);
}

/**
 * Toggle quote mode. When str[0] is a quote and quote mode is off (null-byte),
 * it sets the quote_mode to that type of quote. On later call, when it finds
 * the same quote type, it will set it back to null-byte
 * 
 * @param str any char *
 * @param a pointer to the char to set the quote type
 * 
 * @return 1 if toggle occurred
 * @return 0 otherwise
*/
int	toggle_quote_mode(const char c, char *quote_mode)
{
	if (ft_is_quote(c))
	{
		if (*quote_mode == c)
		{
			*quote_mode = 0;
			return (1);
		}
		if (*quote_mode == 0)
		{
			*quote_mode = c;
			return (1);
		}
	}
	return (0);
}

/**
 * Append a char to the str
 * 
 * @param str any char *
 * @param c any char
 * 
 * @return the resulting char *
 * 
 * @note will free the str passed in the argument
*/
char	*append_char(char *str, char c)
{
	char	*tmp;

	tmp = malloc(ft_strlen(str) + 2);
	ft_memcpy(tmp, str, ft_strlen(str));
	tmp[ft_strlen(str)] = c;
	tmp[ft_strlen(str) + 1] = '\0';
	free(str);
	return (tmp);
}

/**
 * Append a variable to a char *
 * 
 * @param str any char *
 * @param var_name name of the variable
 * @param state pointer to the state struct
 * 
 * @return New char * with the appended variable
 * 
 * @note will free previous str
 * 
 * TODO: remove = and env_name
*/
char	*append_var(char *str, char *var_name, t_state *state)
{
	char	*tmp;
	char	*nb;

	if (*var_name == '?')
	{
		nb = ft_itoa(state->exit_status);
		tmp = ft_strjoin(str, nb);
		free(str);
		free(nb);
		free(var_name);
		return (tmp);
	}
	if (ft_getenv(var_name, state))
	{
		tmp = ft_strjoin(str, ft_getenv(var_name, state));
		free(str);
		str = tmp;
	}
	return (str);
}
