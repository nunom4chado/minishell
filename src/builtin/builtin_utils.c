/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:21:06 by numartin          #+#    #+#             */
/*   Updated: 2023/07/12 18:22:35 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Checks if a command is a builtin
 *
 * @return 1 if true
 * @return 0 if false
*/
int	is_builtin(char **cmd)
{
	if (!cmd || !*cmd)
		return (0);
	if (ft_strcmp(cmd[0], "echo") == 0)
        return (1);
    if (ft_strcmp(cmd[0], "cd") == 0)
        return (1);
    if (ft_strcmp(cmd[0], "pwd") == 0)
        return (1);
    if (ft_strcmp(cmd[0], "export") == 0)
        return (1);
    if (ft_strcmp(cmd[0], "unset") == 0)
        return (1);
    if (ft_strcmp(cmd[0], "env") == 0)
        return (1);
    if (ft_strcmp(cmd[0], "exit") == 0)
    {
        return (1);
    }
	return (0);
}
