/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _expand_unused.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:24:55 by numartin          #+#    #+#             */
/*   Updated: 2023/07/05 16:33:41 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/**
 * @brief Replace the a section in a string with another string
 *
 * @param str the original char *
 * @param replaceable the char * to be inserted
 * @param start position to start replacing
 * @param end position to stop replacing
 *
 * @return pointer to the resulting string
 *
*/
char	*ft_replace_substr(char *str, int start, char *replaceable, int end)
{
	char	*ptr;

	ptr = malloc(ft_strlen(str) + ft_strlen(replaceable) - 1);
	ft_memcpy(ptr, str, start);
	ptr[start] = '\0';
	ft_strcat(ptr, replaceable);
	ft_strcat(ptr, str + start + 1 + end);
	free(str);
	return (ptr);
}

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
