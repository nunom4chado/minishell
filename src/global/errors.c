/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:26:13 by numartin          #+#    #+#             */
/*   Updated: 2023/07/25 12:05:42 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int		g_exit_status;

/**
 *  Display error message and update exit status code
*/
void	print_error(char *msg, int error)
{
	g_exit_status = error;
	printf("%s\n", msg);
}
