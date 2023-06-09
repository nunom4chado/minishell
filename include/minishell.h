/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodos-sa <jodos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:37:18 by numartin          #+#    #+#             */
/*   Updated: 2023/06/09 16:44:50 by jodos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include "libft.h"

# define EXEC 1
# define REDIR 2
# define PIPE 3
# define LIST 4

/* typedef struct s_token
{
	int	type;
	t_token	*left;
	t_token	*right;
}			t_token; */

typedef struct s_state
{
	int	exit_status;
	char	**envp;
}		t_state;



/* --------------------------------- Signals ------------------------------- */
void	handle_ctrl_c(int signo);
int		handle_ctrl_d(char *cmd);
int		typed_exit(char *cmd);
/* ------------------------------------------------------------------------- */

/* --------------------------------- Path ---------------------------------- */
char	*path(char *cmd, char **envp);
/* ------------------------------------------------------------------------- */

/* --------------------------------- CMD ----------------------------------- */
void	last_cmd(char *comand, t_state *state);
/* ------------------------------------------------------------------------- */

/* --------------------------------- CD_CMD -------------------------------- */
void	cd_cmd(char *cmd, t_state *state);
/* ------------------------------------------------------------------------- */

/* --------------------------------- Env ----------------------------------- */
int		ft_setenv(char *key, char *newvalue, t_state *state);
char	*ft_getenv(char *key, t_state *state);
/* ------------------------------------------------------------------------- */

/* --------------------------------- Expand -------------------------------- */
char	*expand(char *cmd, t_state *state);
/* ------------------------------------------------------------------------- */

/* --------------------------------- Utils --------------------------------- */
void	free_split(char **args);
int		ft_strcmp(char *s1, char *s2);
char *ft_strcat(char *dest, char *src);
/* ------------------------------------------------------------------------- */

#endif
