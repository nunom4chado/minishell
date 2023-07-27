/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 13:23:20 by numartin          #+#    #+#             */
/*   Updated: 2023/07/25 11:41:36 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int		g_exit_status;

/**
 * Execute pwd builtin
*/
void	builtin_pwd(void)
{
	char	pwd[256];

	getcwd(pwd, sizeof(pwd));
	printf("%s\n", pwd);
	g_exit_status = 0;
}
