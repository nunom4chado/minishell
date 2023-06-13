/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodos-sa <jodos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:37:18 by numartin          #+#    #+#             */
/*   Updated: 2023/06/13 17:45:26 by jodos-sa         ###   ########.fr       */
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

typedef struct s_word
{
	char	*word;
	int		space;
	struct s_word	*next;
	//t_word	*prev;
}		t_word;

typedef struct s_state
{
	int	exit_status;
	char	*cmd;
	char	**envp;
	t_word	*words;
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
void	last_cmd(t_state *state);
/* ------------------------------------------------------------------------- */

/* --------------------------------- CD_CMD -------------------------------- */
void	cd_cmd(t_state *state);
/* ------------------------------------------------------------------------- */

/* --------------------------------- Env ----------------------------------- */
int		ft_setenv(char *key, char *newvalue, t_state *state);
char	*ft_getenv(char *key, t_state *state);
/* ------------------------------------------------------------------------- */

/* --------------------------------- Expand -------------------------------- */
char	*expand(t_state *state);
/* ------------------------------------------------------------------------- */

/* --------------------------------- Utils --------------------------------- */
void	free_split(char **args);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcat(char *dest, char *src);
char	*ft_read_until(char *cmd);
int		handle_builtin(t_state *state, int *count);
int	ft_split_words(t_state *state, char *input);
/* ------------------------------------------------------------------------- */

/* ------------------------------- List Utils ------------------------------- */
void	ft_word_add_back(t_word **lst, t_word *new);
t_word	*ft_last_word(t_word *lst);
t_word	*ft_new_word(void *word, int space);

#endif
