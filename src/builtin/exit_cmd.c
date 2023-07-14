/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 13:30:47 by numartin          #+#    #+#             */
/*   Updated: 2023/07/14 13:31:58 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_state		g_state;

/**
 * Exit the shell with status code saved on state and free all memory.
 *
 * @note exit will only work if has 0 arguments
*/
void	exit_builtin(char **cmd, t_state *state)
{
	int	len;
	int exit_code;

	len = -1;
	if (has_pipe(state))
		return ;
	while (cmd[++len]);
	printf("exit\n");
	if (len > 2)
	{
		print_error("too many arguments", 1);
		return ;
	}
	if (len == 1)
		clean_all(state);
	if (len == 2)
	{
		if (ft_isnumber(cmd[1]))
		{
			clean_all(state);
			exit_code = (char)ft_atoi(cmd[1]);
			free_2d_array(cmd);
			exit(exit_code);
		}
		else
		{
			print_error("numeric argument required", 2);
			clean_all(state);
		}
	}
	free_2d_array(cmd);
	exit(state->exit_status);
}