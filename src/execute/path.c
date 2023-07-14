/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:13:02 by jodos-sa          #+#    #+#             */
/*   Updated: 2023/07/14 14:34:57 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_possible_path(char *envpath, char *cmd)
{
	char	*path;
	char	*f_slash;

	if (ft_strncmp(envpath, cmd, ft_strlen(envpath)) == 0)
		path = ft_strdup(cmd);
	else
	{
		f_slash = ft_strjoin(envpath, "/");
		path = ft_strjoin(f_slash, cmd);
		free(f_slash);
	}
	return (path);
}

int	is_executable(char *cmd_path)
{
	if (!access(cmd_path, F_OK))
		return (1);
	return (0);
}

char	*get_absolute_path(char *cmd, char *path_variable)
{
	char		**all_paths;
	char		*cmd_path;
	int			i;

	i = 0;
	all_paths = ft_split(path_variable, ':');
	while (all_paths && all_paths[i])
	{
		cmd_path = get_possible_path(all_paths[i], cmd);
		if (is_executable(cmd_path))
			break ;
		free(cmd_path);
		cmd_path = NULL;
		i++;
	}
	free_split(all_paths);
	return (cmd_path);
}

char	**get_paths(char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	paths = NULL;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	return (paths);
}

char	*path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*f_slash;
	int		i;

	i = 0;
	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
		return (cmd);
	paths = get_paths(envp);
	i = -1;
	while (paths[++i])
	{
		f_slash = ft_strjoin(paths[i], "/");
		path = ft_strjoin(f_slash, cmd);
		free(f_slash);
		if (!access(path, F_OK))
		{
			free_split(paths);
			return (path);
		}
		free(path);
	}
	free_split(paths);
	return (0);
}
