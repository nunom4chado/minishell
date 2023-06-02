/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodos-sa <jodos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:17:35 by jodos-sa          #+#    #+#             */
/*   Updated: 2023/06/02 18:32:01 by jodos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//				UPDATE OLDPWD
void	cd_cmd(char *cmd, t_state *state)
{
	char	*path;
	char	*home;

	path = ft_strtrim(cmd + 3, " ");
	if (chdir(path) < 0)
	{
		if (*path == '\0')
			state->exit_status = chdir(getenv("HOME"));
		else if (*path == '~')
		{
			home = ft_strjoin(getenv("HOME"), path + 1);
			state->exit_status = chdir(home);
			free(home);
		}
		else if (*path == '-' && *(path + 1) == '-' && *(path + 2) == '\0')
			state->exit_status = chdir(getenv("HOME"));
		else if (*path == '-' && *(path + 1) == '\0')
		{
			printf("%s\n", getenv("OLDPWD"));
			state->exit_status = chdir(getenv("OLDPWD")); 
		}
		else
		{
			state->exit_status = 1;
			perror("cd");
		}
	}
	else
		state->exit_status = 0;
}
