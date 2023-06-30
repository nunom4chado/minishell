/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:38:22 by numartin          #+#    #+#             */
/*   Updated: 2023/06/30 14:23:45 by numartin         ###   ########.fr       */
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
 * TODO: remove = in ft_getenv after merge
*/
void	ft_tilde_expand(t_token *token, t_state *state)
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
