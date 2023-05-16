NAME	:= minishell
CC		:= cc
CFLAGS	:= -Wall -Werror -Wextra -Iinclude
DEPS	:= -lreadline

SRC_DIR	:= ./src/
OBJ_DIR	:= ./obj/

SRC		:= main.c

SOURCES	:= $(addprefix $(SRC_DIR), $(SRC))
OBJS	:= $(SRC:.c=.o)
OBJ		:= $(addprefix $(OBJ_DIR), $(OBJS))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(DEPS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
