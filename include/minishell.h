/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodos-sa <jodos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:37:18 by numartin          #+#    #+#             */
/*   Updated: 2023/05/18 16:43:14 by jodos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
#include "libft.h"



char	*path(char *cmd, char **envp);

void	free_split(char **args);

void	open_cmd(int *pipefd,int fd, char *cmd, char **envp);
void	last_cmd(int *pipefd,int fd, char *comand, char **envp);
