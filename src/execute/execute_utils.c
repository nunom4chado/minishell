/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 19:48:54 by numartin          #+#    #+#             */
/*   Updated: 2023/07/27 14:46:20 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Free all data if execution failed
*/
void	handle_execution_error(char **env, char **cmd, t_state *state)
{
	printf("minishell: command not found\n");
	free_split(env);
	free_split(cmd);
	clean_all(state);
	exit(127);
}
