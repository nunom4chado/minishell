/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 13:30:47 by numartin          #+#    #+#             */
/*   Updated: 2023/07/25 14:51:30 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int		g_exit_status;

void	handle_exit_with_two_args(char **cmd, t_state *state)
{
	int	exit_code;

	if (ft_isnumber(cmd[1]))
	{
		clean_all(state);
		exit_code = (char)ft_atoi(cmd[1]);
		free_split(cmd);
		exit(exit_code);
	}
	else
	{
		print_error("numeric argument required", 2);
		clean_all(state);
	}
}

/**
 * Exit the shell with status code saved on state and free all memory.
*/
void	exit_builtin(char **cmd, t_state *state)
{
	int	len;

	len = 0;
	if (has_pipe(state))
		return ;
	while (cmd[len])
		len++;
	printf("exit\n");
	if (len > 2)
	{
		print_error("too many arguments", 1);
		return ;
	}
	if (len == 1)
		clean_all(state);
	if (len == 2)
		handle_exit_with_two_args(cmd, state);
	free_split(cmd);
	exit(g_exit_status);
}
