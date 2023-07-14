/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:17:35 by jodos-sa          #+#    #+#             */
/*   Updated: 2023/07/14 13:39:21 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Update OLDWD
*/
void	update_oldpwd(t_state *state)
{
	char	newpwd[256];

	getcwd(newpwd, sizeof(newpwd));
	ft_setenv("OLDPWD", ft_getenv("PWD", state), state);
	ft_setenv("PWD", newpwd, state);
}

/**
 * Update PWD
 * 
 * @return 0 or positive int on success
 * @return -1 on error
*/
int	handle_cd(char *path, t_state *state)
{
	state->exit_status = chdir(path);
	if (state->exit_status < 0)
		return (state->exit_status);
	update_oldpwd(state);
	return (state->exit_status);
}

/**
 * Execute cd builtin command
 * 
 * @param state global state
 * @param cmd array of command (0 index) and args
*/
void	builtin_cd(t_state *state, char **cmd)
{
	char	*path;

	path = cmd[0];
	if (cmd[0] && cmd[1])
	{
		print_error("too many arguments", 1);
		state->exit_status = 1;
		return ;
	}
	if (path == NULL || *path == '\0')
		path = ft_getenv("HOME", state);
	else if (*path == '-' && *(path + 1) == '-' && *(path + 2) == '\0')
		path = ft_getenv("HOME", state);
	else if (*path == '-' && *(path + 1) == '\0')
	{
		printf("%s\n", ft_getenv("OLDPWD", state));
		path = ft_getenv("OLDPWD", state);
	}
	if (handle_cd(path, state) < 0)
	{
		state->exit_status = 1;
		perror("cd");
	}
}
