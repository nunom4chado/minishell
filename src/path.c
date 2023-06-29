/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodos-sa <jodos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:13:02 by jodos-sa          #+#    #+#             */
/*   Updated: 2023/06/29 15:29:31 by jodos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths(char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	paths = NULL;
	//while (!ft_strnstr(envp[i], "PATH=", 5))
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
