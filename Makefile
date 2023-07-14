_END		=	\e[0m
_BOLD		=	\e[1m
_UNDER		=	\e[4m
_REV		=	\e[7m


_GREY		=	\e[1;30m
_RED		=	\e[1;31m
_GREEN		=	\e[1;32m
_YELLOW		=	\e[1;33m
_BLUE		=	\e[1;34m
_PURPLE		=	\e[1;35m
_CYAN		=	\e[1;36m
_WHITE		=	\e[1;37m


_GONE		=	\e[2K\r


NAME		:=	minishell
CC			:=	cc
CFLAGS		:=	-Wall -Werror -Wextra -g #-fsanitize=address
DEPS		:=	-lreadline -lXext -lX11 -lm


INCLUDE		=	-I ./include/\
				-I ./libft/

LIB_PATH	=	./libft/
LIB_NAME	=	libft.a
LIB			=	$(LIB_PATH)$(LIB_NAME)

SRC_DIR		:=	./src/
OBJ_DIR		:=	./obj/

BUILTIN_DIR	:=	builtin/
EXECUTE_DIR	:=	execute/
EXPORT_DIR	:=	export/
GLOBAL_DIR	:=	global/
LEXAR_DIR	:=	lexar/
PARSER_DIR	:=	parser/
SIGNALS_DIR	:=	signals/


BUILTIN		:=	builtin.c \
				cd_cmd.c \
				echo_cmd.c \
				exit_cmd.c \
				export_cmd.c \
				pwd_cmd.c \
				unset_cmd.c

EXECUTE		:=	path.c \
				execute.c

EXPORT		:=	env_utils.c \
				env.c \
				export_utils.c \
				export.c \
				unset_utils.c \
				unset.c

GLOBAL		:=	cleanup.c \
				debug.c \
				errors.c \
				init.c \
				utils.c \
				utils2.c

LEXAR		:=	expand_utils.c \
				expand.c \
				input.c \
				lexar_utils.c \
				lexar_utils2.c \
				lexar.c \
				lst_tokens.c

PARSER		:=	parser.c \
				heredoc.c \
				create_cmd.c

SIGNALS		:=	signals_exec.c \
				signals_heredoc.c \
				signals.c

BUILTIN_SRC	:=	$(addprefix $(BUILTIN_DIR), $(BUILTIN))
EXECUTE_SRC	:=	$(addprefix $(EXECUTE_DIR), $(EXECUTE))
EXPORT_SRC	:=	$(addprefix $(EXPORT_DIR), $(EXPORT))
GLOBAL_SRC	:=	$(addprefix $(GLOBAL_DIR), $(GLOBAL))
LEXAR_SRC	:=	$(addprefix $(LEXAR_DIR), $(LEXAR))
PARSER_SRC	:=	$(addprefix $(PARSER_DIR), $(PARSER))
SIGNALS_SRC	:=	$(addprefix $(SIGNALS_DIR), $(SIGNALS))


SRC			:=	$(BUILTIN_SRC) \
				$(EXECUTE_SRC) \
				$(EXPORT_SRC) \
				$(GLOBAL_SRC) \
				$(LEXAR_SRC) \
				$(PARSER_SRC) \
				$(SIGNALS_SRC) \
				main.c

SOURCES		:=	$(addprefix $(SRC_DIR), $(SRC))
OBJS		:=	$(SRC:.c=.o)
OBJ			:=	$(addprefix $(OBJ_DIR), $(OBJS))

all: $(LIB) $(NAME)

$(LIB):
	@printf "$(_GONE)$(_YELLOW) Making LIBFT... $(_END)\n"
	@make -sC $(LIB_PATH)
	@printf "$(_GONE)$(_GREEN) LIBFT Created. $(_END)\n"
	@printf "$(_GONE)$(_BLUE) ============================================ $(_END)\n"

$(NAME): $(OBJ)
	@printf "\033[2K\r$(_GREEN) All files compiled into '$(OBJ_DIR)'. $(_END)\n"
	@$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIB) $(INCLUDE) $(DEPS)
	@printf "\033[2K\r$(_GREEN) Executable '$(NAME)' created. $(_END)\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

$(OBJ_DIR):
	@mkdir -p $@
	@mkdir -p $@/builtin
	@mkdir -p $@/execute
	@mkdir -p $@/export
	@mkdir -p $@/global
	@mkdir -p $@/lexar
	@mkdir -p $@/parser
	@mkdir -p $@/signals

clean:
	@make -sC $(LIB_PATH) clean
	@rm -rf $(OBJ_DIR)
	@printf "\033[2K\r$(_RED) '"$(OBJ_DIR)"' has been deleted. $(_END)\n"

fclean: clean
	@make -sC $(LIB_PATH) fclean
	@rm -f $(NAME)
	@printf "\033[2K\r$(_RED) '"$(NAME)"' has been deleted. $(_END)\n"

re: fclean all

rerun: re
	@./$(NAME)

valgrind: re
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline_supression ./minishell

.PHONY: all clean fclean re valgrind revalgrind rerun
