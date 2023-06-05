/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:17:35 by jodos-sa          #+#    #+#             */
/*   Updated: 2023/06/05 18:39:23 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_oldpwd(t_state *state)
{
	int i;
	char	newpwd[256];

	i = 0;
	getcwd(newpwd, sizeof(newpwd));
	ft_setenv("OLDPWD=", ft_strjoin("OLDPWD=", ft_getenv("PWD=", state)), state);
	ft_setenv("PWD=", ft_strjoin("PWD=", newpwd), state);
}

int	handle_cd(char *path, t_state *state)
{
	state->exit_status = chdir(path);
	if (state->exit_status < 0)
		return (state->exit_status);
	// update oldpwd
	update_oldpwd(state);

	return (state->exit_status);
}

void	cd_cmd(char *cmd, t_state *state)
{
	char	*path;
	char	*home;

	path = ft_strtrim(cmd + 3, " ");
	if (handle_cd(path, state) < 0)
	{
		if (*path == '\0')
			handle_cd(getenv("HOME"), state);
		else if (*path == '~')
		{
			home = ft_strjoin(getenv("HOME"), path + 1);
			handle_cd(home, state);
			free(home);
		}
		else if (*path == '-' && *(path + 1) == '-' && *(path + 2) == '\0')
			handle_cd(getenv("HOME"), state);
		else if (*path == '-' && *(path + 1) == '\0')
		{
			printf("%s\n", getenv("OLDPWD"));
			handle_cd(getenv("OLDPWD"), state);
		}
		else
		{
			state->exit_status = 1;
			perror("cd");
		}
	}
}
