NAME	:= minishell
CC		:= cc
CFLAGS	:= -Wall -Werror -Wextra
DEPS	:= -lreadline -lXext -lX11 -lm


INCLUDE		=	-I ./include/\
				-I ./libft/

SRC_DIR	:= ./src/
OBJ_DIR	:= ./obj/

LIB_PATH	= ./libft/
LIB_NAME	= libft.a
LIB			= $(LIB_PATH)$(LIB_NAME)

SRC		:=	main.c \
			path.c \
			utils.c \
			cmd.c

SOURCES	:= $(addprefix $(SRC_DIR), $(SRC))
OBJS	:= $(SRC:.c=.o)
OBJ		:= $(addprefix $(OBJ_DIR), $(OBJS))

all: $(LIB) $(NAME)

$(LIB):
	@printf "Making LIBFT..."
	@make -sC $(LIB_PATH)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIB) $(INCLUDE) $(DEPS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

$(OBJ_DIR):
	mkdir -p $@

clean:
	@make -sC $(LIB_PATH) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	@make -sC $(LIB_PATH) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
