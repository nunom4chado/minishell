/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:17:17 by numartin          #+#    #+#             */
/*   Updated: 2023/06/12 17:58:07 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void	builtin_export(t_state *state)
{
	char	*path;
	char	*key;
	char	*value;

	path = ft_strtrim(state->cmd + 6, " \t\v");
	if (path && *path)
	{
		// path will be something like this "KEY=value"

		// ensure pattern is OK and has a value
		// extract key name
		// extract value
		ft_setenv(key, value, state);
	}

	// Does count increment if export failed?
}
 */
int	handle_builtin(t_state *state, int *count)
{
	if (state->cmd[0] == 'c' && state->cmd[1] == 'd' && (state->cmd[2] == ' ' || state->cmd[2] == '\0'))
	{
		cd_cmd(state);
		*count = *count + 1;
		return 1;
	}
	if (ft_strncmp(state->cmd, "export", 6) == 0 && (state->cmd[7] == ' ' || state->cmd[7] == '\0'))
	{
		//builtin_export(state);
		*count = *count + 1;
		return 1;
	}
	return (0);
}
