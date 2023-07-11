/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:26:13 by numartin          #+#    #+#             */
/*   Updated: 2023/07/11 12:02:25 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_state		g_state;

/**
 *  TODO: display msg and update exit status
*/
void	print_error(char *msg, int error)
{
	g_state.exit_status = error;
	printf("%s\n", msg);
}
