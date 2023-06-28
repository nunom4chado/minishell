/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:38:22 by numartin          #+#    #+#             */
/*   Updated: 2023/06/28 15:52:04 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * If a variable is not in env, skip that parte and join both ends
 *
 * @param str char * cointaining a portion to be removed
 * @param start position to start removing
 * @param end position to stop removing
 *
 * @return char * of the resulted join
*/
char	*skip_undefined_var(char *str, int start, int end)
{
	char	*new;

	new = malloc(ft_strlen(str) - end + start + 1);
	ft_memcpy(new, str, start);
	new[start] = '\0';
	ft_strcat(new, str + start + 1 + end);
	free(str);
	return (new);
}

/**
 * @brief Replace the variable name with the variable value
 *
 * @param str the original char *
 * @param expandable the char * to be inserted
 * @param start position to start replacing
 * @param end position to stop replacing
 *
 * @return pointer to the resulting string
 *
*/
char	*ft_expand_var(char *str, int start, char *expandable, int end)
{
	char	*ptr;

	ptr = malloc(ft_strlen(str) + ft_strlen(expandable) - 1);
	ft_memcpy(ptr, str, start);
	ptr[start] = '\0';
	ft_strcat(ptr, expandable);
	ft_strcat(ptr, str + start + 1 + end);
	free(str);
	return (ptr);
}

/**
 * Expand tilde in a token.
 *
 * @note It will only expand if the first char is '~' and the second is '\0' or '/'
 *
 * @param token pointer to the token to be expanded
 * @param state pointer to the program state struct
*/
void ft_tilde_expand(t_token *token, t_state *state)
{
	char	*tmp;

	if (token->word[0] == '~')
	{
		if (token->word[1] == '\0' || token->word[1] == '/')
		{
			// TODO: remove =
			tmp = ft_strjoin(ft_getenv("HOME=", state), token->word + 1);
			free(token->word);
			token->word = tmp;
		}
	}
}

/**
 * Remove invalid variable from the token
 *
 * @note In this implementation, if the next character after '$' is not
 * '_', alpha char or '?', both the first and second chars will be
 * skipped and not saved
 *
 * @param token pointer to a token
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
	int i;

	i = 0;
	if (str[i] == '?')
		return(ft_substr(str, 0, 1));
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return(ft_substr(str, 0, 1));
	while(str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return(ft_substr(str, 0, i));
}
