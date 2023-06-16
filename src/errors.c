/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:26:13 by numartin          #+#    #+#             */
/*   Updated: 2023/06/16 14:30:41 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    handle_unexpected_eof(char *added_input, char *input, t_state *state)
{
    if (!added_input)
	{
		(void)state;
		// hitting ctr-d will send EOF, in this case will throw an error
		// because input was not complete
		printf("syntax error: unexpected end of file\nexit\n");
		free(input);
		// TODO: handle leaking state, show correct exit status
		exit(EXIT_FAILURE);
	}

}