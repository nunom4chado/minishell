/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:54:52 by numartin          #+#    #+#             */
/*   Updated: 2023/06/15 11:46:51 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_input_error(char *msg, char *input, t_state *state)
{
	printf("%s\n", msg);
	free(input);
	lst_token_clear(&(state->tokens), free);
}