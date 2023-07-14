/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:13:02 by jodos-sa          #+#    #+#             */
/*   Updated: 2023/07/14 15:39:20 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Prepend path to command
 * 
 * @param envpath path to prepend
 * @param cmd the command
 * 
 * @note if command start with '.' or '/' will not prepend
*/
static char	*prepend_path(char *envpath, char *cmd)
{
	char	*path;
	char	*f_slash;

	if (cmd[0] == '/' || cmd[0] == '.')
		path = ft_strdup(cmd);
	else
	{
		f_slash = ft_strjoin(envpath, "/");
		path = ft_strjoin(f_slash, cmd);
		free(f_slash);
	}
	return (path);
}

/**
 * Check if the command is an executable
*/
int	is_executable(char *cmd_path)
{
	if (!access(cmd_path, F_OK))
		return (1);
	return (0);
}

/**
 * Will update cmd to prepend path to it, unless it starts with '.' or '/'
*/
char	*get_absolute_path(char *cmd, char *path_variable)
{
	char		**all_paths;
	char		*cmd_path;
	int			i;

	i = 0;
	all_paths = ft_split(path_variable, ':');
	while (all_paths && all_paths[i])
	{
		cmd_path = prepend_path(all_paths[i], cmd);
		if (is_executable(cmd_path))
			break ;
		free(cmd_path);
		cmd_path = NULL;
		i++;
	}
	free_split(all_paths);
	return (cmd_path);
}
