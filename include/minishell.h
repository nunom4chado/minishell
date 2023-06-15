/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:37:18 by numartin          #+#    #+#             */
/*   Updated: 2023/06/15 18:28:10 by numartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* -------------------------------------------------------------------------- */
/*                                  Includes                                  */
/* -------------------------------------------------------------------------- */
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

/* -------------------------------------------------------------------------- */
/*                                   Defines                                  */
/* -------------------------------------------------------------------------- */
# define EXEC 1
# define REDIR 2
# define PIPE 3
# define LIST 4

/* -------------------------------------------------------------------------- */
/*                                   Structs                                  */
/* -------------------------------------------------------------------------- */
/* typedef struct s_token
{
	int	type;
	t_token	*left;
	t_token	*right;
}			t_token; */

typedef struct s_token
{
	char	*word;
	int		space;
	struct s_token	*next;
	//t_token	*prev;
}		t_token;

typedef struct s_state
{
	int		exit_status;
	char	*heredoc;
	char	*cmd;
	char	**envp;
	t_token	*tokens;
}		t_state;

/* -------------------------------------------------------------------------- */
/*                                 Prototypes                                 */
/* -------------------------------------------------------------------------- */

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
int		ft_is_space(char c);
int		ft_is_quote(char c);
int		ft_is_specialchar(char c);
int		ft_is_redirect(char c);
int		ft_only_spaces(char *c);
void	free_split(char **args);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcat(char *dest, char *src);
char	*ft_read_until(char *cmd);

int		handle_builtin(t_state *state, int *count);
/* ------------------------------------------------------------------------- */





/* ------------------------------- List Tokens ------------------------------ */

t_token	*lst_new_token(void *word, int space);
t_token	*lst_last_token(t_token *lst);
void	lst_token_add_back(t_token **lst, t_token *new);
void	lst_token_clear(t_token **lst, void (*del)(void *));

/* -------------------------------- Tokenizer ------------------------------- */

int		tokenizer(t_state *state, char *input);

/* ------------------------------- Token Utils ------------------------------ */

char	*ft_split_specialchar(char *input, t_state *state);
char	*ft_split_quotes(t_state *state, char *input);
char	*advance_quotes(char *input, char quote_type, t_state *state);
char	*create_token(char *input, char *end, t_state *state);
char	*handle_normal_token(char *input, t_state *state);

/* ---------------------------- Token validation ---------------------------- */

int		validate_last_token(t_state *state);
int		validate_token_sequence(char *input, t_state *state);

/* -------------------------------- Clean up -------------------------------- */

void	clean_input(char *input, t_state *state);

/* ---------------------------------- Debug --------------------------------- */

void	print_tokens(t_state *state);

#endif
