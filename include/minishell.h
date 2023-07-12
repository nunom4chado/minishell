/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:37:18 by numartin          #+#    #+#             */
/*   Updated: 2023/07/12 10:57:34 by numartin         ###   ########.fr       */
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
# define CODE_SYNTAX_ERROR 2
# define CODE_CMD_NOT_FOUND 127

# define IN 0
# define OUT 1

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
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_FILE,
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

typedef struct s_env
{
	char	*key;
	char	*value;
	struct	s_env	*next;
}				t_env;

typedef struct s_export
{
	char	*key;
	char	*value;
	struct	s_export	*next;
}				t_export;

typedef struct s_state
{
	int		exit_status;
	char	*input;
	int		echo;
	t_env	*env;
	t_export	*exp;
	t_token	*tokens;
}		t_state;

/* -------------------------------------------------------------------------- */
/*                                 Prototypes                                 */
/* -------------------------------------------------------------------------- */

/*-------------------------------- Builtin -------------------------------*/

void	execute_builtin(char **cmd, t_state *state);
int		is_builtin(char **cmd);
void	exit_builtin(char **cmd, t_state *state);

/* --------------------------------- CD_CMD -------------------------------- */

void	cd_cmd(t_state *state, char **cmd);

/* -------------------------------- Clean up -------------------------------- */

void	clean_last_cmd(t_state *state);
void	clean_all(t_state *state);
void	free_2d_array(char **ptr);

/* --------------------------------- CMD ----------------------------------- */

//void	last_cmd(t_state *state);
void	execute(char **cmd);
char	**array_env(t_state *state);

/* ---------------------------------- Debug --------------------------------- */

void	print_tokens(t_state *state);
void	print_arr_str(char **arr, char *msg);

/* --------------------------------- Env ----------------------------------- */

t_env	*ft_newenv(void *key, void *value);
void	ft_addenv_back(t_env **lst, t_env *new);
void	create_env(t_state *state, char **envi);
t_env	*findenv(t_state *state, char *key);
int		ft_setenv(char *key, char *newvalue, t_state *state);
char	*ft_getenv(char *key, t_state *state);
void	print_env(t_state *state);

/* --------------------------------- Errors --------------------------------- */

void	print_error(char *msg, int error);

/* --------------------------------- Expand -------------------------------- */

void	expand(t_state *state);
char	*skip_undefined_var(char *str, int start, int end);
void	ft_tilde_expand(t_token *token, t_state *state);
char	*find_var_name(char *str);
int		can_expand(const char *str, char quote_mode);
int		toggle_quote_mode(const char c, char *quote_mode);
char	*append_char(char *str, char c);
char	*append_var(char *str, char *var_name, t_state *state);

/*--------------------------------- Export -------------------------------*/

t_export	*ft_newexp(void *key, void	*value);
void	ft_addexp(t_export **lst, t_export *new);
void	create_exp(t_state *state, char **envi);
void	print_export(t_state *state);
t_export	*findexp(t_state *state, char *key);
int	ft_setexp(char *key, char *newvalue, t_state *state);
char	*ft_getexp(char *key, t_state *state);

/* ---------------------------------- Init ---------------------------------- */

void	init_state(t_state *state);

/* ---------------------------------- Input --------------------------------- */

int		process_input(t_state *state);
char	*prompt_style(t_state *state);

/* ---------------------------------- Lexar --------------------------------- */

int		lexar(t_state *state, char *input);
char	*ft_split_specialchar(char *input, t_state *state);
char	*create_token(char *input, char *end, t_tk_type type, t_state *state);
char	*handle_normal_token(char *input, t_state *state);
int		validate_last_token(t_state *state);
int		validate_token_sequence(char *input, t_state *state);
int		pending_pipe(t_state *state);
int		has_heredocs(t_state *state);

/* ------------------------------- List Tokens ------------------------------ */

t_token	*lst_token_new(void *word, t_tk_type type);
t_token	*lst_token_last(t_token *lst);
void	lst_token_add_back(t_token **lst, t_token *new);
void	lst_token_clear(t_token **lst, void (*del)(void *));
int		lst_token_size(t_token *lst);

/* --------------------------------- Parser --------------------------------- */

void	parse_and_execute(t_state *state);
int		has_pipe(t_state *state);
char	**compose_cmd(t_state *state);
char	**create_command_array(t_token *token, t_token *pipe);
void	here_doc_input(char *eof, int *save_fd);

/* --------------------------------- Path ---------------------------------- */

char	*path(char *cmd, char **envp);
char	*get_absolute_path(char *cmd, char *path_variable);

/* --------------------------------- Signals ------------------------------- */

void	register_signals(void);
void	handle_ctrl_c(int signo);
int		handle_ctrl_d(char *cmd, t_state *state);
void	define_exec_signals(void);

/*-------------------------------- Unset ------------------------------*/

void	ft_expdelone(t_export *lst);
void	ft_envdelone(t_env *lst);
void	ft_delete_export(t_export *lst);
void	ft_delete_env(t_env *lst);
void	unset_expvariables(t_state *state, char *key);
void	unset_envvariables(t_state *state, char *key);

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
int		ft_isnumber(char *str);

#endif
