/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:37:18 by numartin          #+#    #+#             */
/*   Updated: 2023/06/26 14:56:10 by numartin         ###   ########.fr       */
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

# define PROMPT_DEFAULT "minishell> "
# define PROMPT_PIPE "pipe> "
# define PROMPT_HEREDOC "heredoc> "
# define PROMPT_PIPE_HEREDOC "pipe heredoc> "

# define CODE_CTR_C 130

/* -------------------------------------------------------------------------- */
/*                                   Structs                                  */
/* -------------------------------------------------------------------------- */
/* typedef struct s_token
{
	int	type;
	t_token	*left;
	t_token	*right;
}			t_token; */

// WARNING: when changing these values you must also update in debug functions
typedef enum e_tk_type
{
	WORD,
	EXEC,
	ARG,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	HEREDOC_DELIMITER,
}	t_tk_type;

typedef struct s_token
{
	t_tk_type		type;
	char			*word;
	struct s_token	*next;
	struct s_token	*prev;
}		t_token;

typedef struct s_state
{
	int		exit_status;
	char	*input;
	char	*cmd;
	char	**envp;
	t_token	*heredocs;
	t_token	*tokens;
}		t_state;

/* -------------------------------------------------------------------------- */
/*                                 Prototypes                                 */
/* -------------------------------------------------------------------------- */

/* --------------------------------- Signals ------------------------------- */
void	handle_ctrl_c(int signo);
int		handle_ctrl_d(char *cmd, t_state *state);
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



/* ---------------------------------- Init ---------------------------------- */

void    init_state(t_state *state, char **environ);

/* ------------------------------ Process input ----------------------------- */

int		process_input(char *input, t_state *state);
int		pending_pipe(t_state *state);
char	*prompt_style(t_state *state);

/* ------------------------------- List Tokens ------------------------------ */

t_token	*lst_new_token(void *word, t_tk_type type);
t_token	*lst_last_token(t_token *lst);
void	lst_token_add_back(t_token **lst, t_token *new);
void	lst_token_clear(t_token **lst, void (*del)(void *));

/* ---------------------------------- Lexar --------------------------------- */

int		lexar(t_state *state, char *input);

/* ------------------------------- Token Utils ------------------------------ */

char	*ft_split_specialchar(char *input, t_state *state);
char	*ft_split_quotes(t_state *state, char *input);
char	*advance_quotes(char *input, char quote_type, t_state *state);
char	*create_token(char *input, char *end, t_tk_type type, t_state *state);
char	*handle_normal_token(char *input, t_state *state);

/* ---------------------------- Token validation ---------------------------- */

int		validate_last_token(t_state *state);
int		validate_token_sequence(char *input, t_state *state);

/* -------------------------------- Clean up -------------------------------- */

void	clean_input(char *input, t_state *state);

/* ---------------------------------- Debug --------------------------------- */

void	print_tokens(t_state *state);
void	print_heredocs(t_state *state);

/* --------------------------------- Errors --------------------------------- */


void    apply_prompt_style(char *prompt, t_state *state);


#endif
