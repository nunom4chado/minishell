/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodos-sa <jodos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:17:35 by jodos-sa          #+#    #+#             */
/*   Updated: 2023/06/10 16:06:41 by jodos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_oldpwd(t_state *state)
{
	int i;
	char	newpwd[256];

	i = 0;
	getcwd(newpwd, sizeof(newpwd));
	ft_setenv("OLDPWD=", ft_getenv("PWD=", state), state);
	ft_setenv("PWD=", newpwd, state);
}

int	handle_cd(char *path, t_state *state)
{
	state->exit_status = chdir(path);
	if (state->exit_status < 0)
		return (state->exit_status);
	update_oldpwd(state);
	return (state->exit_status);
}

void	cd_cmd(char *cmd, t_state *state)
{
	char	*path;
	
	path = ft_strtrim(cmd + 3, " ");
 	if (*path == '\0')
		path = ft_getenv("HOME=", state);
	else if (*path == '-' && *(path + 1) == '-' && *(path + 2) == '\0')
		path = ft_getenv("HOME=", state);
	else if (*path == '-' && *(path + 1) == '\0')
	{
		printf("%s\n", ft_getenv("OLDPWD=", state));
		path = ft_getenv("OLDPWD=", state);
	}
	if (handle_cd(path, state) < 0)
	{
		state->exit_status = 1;
		perror("cd");
	}
	/* if (handle_cd(path, state) < 0)
	{
		//printf("ERROR:%s\n", path);
		if (*path == '\0')
			handle_cd(ft_getenv("HOME=", state), state);
		else if (*path == '-' && *(path + 1) == '-' && *(path + 2) == '\0')
			handle_cd(ft_getenv("HOME=", state), state);
		else if (*path == '-' && *(path + 1) == '\0')
		{
			printf("%s\n", ft_getenv("OLDPWD=", state));
			handle_cd(ft_getenv("OLDPWD=", state), state);
		}
		else
		{
			state->exit_status = 1;
			perror("cd");
		}
	} */
}
