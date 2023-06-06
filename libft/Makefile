# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jodos-sa <jodos-sa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 12:05:15 by jodos-sa          #+#    #+#              #
#    Updated: 2023/06/06 14:15:19 by jodos-sa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a
LIBC		=	ar rc
CC			=	cc
RM			=	rm -f
CFLAGS		=	-Wall -Wextra -Werror

SRC			=	ft_isalpha.c \
				ft_isdigit.c \
				ft_isalnum.c \
				ft_isascii.c \
				ft_isprint.c \
				ft_strlen.c \
				ft_memset.c \
				ft_bzero.c \
				ft_memcpy.c\
				ft_memmove.c \
				ft_strlcpy.c \
				ft_strlcat.c \
				ft_toupper.c \
				ft_tolower.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_strncmp.c \
				ft_memchr.c\
				ft_memcmp.c \
				ft_strnstr.c \
				ft_atoi.c \
				ft_calloc.c \
				ft_strdup.c \
				ft_substr.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_split.c\
				ft_itoa.c \
				ft_strmapi.c \
				ft_striteri.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c

OBJ_PATH	=	./obj/
OBJS		=	$(SRC:.c=.o)
OBJ			=	$(addprefix $(OBJ_PATH), $(OBJS))		

BONUS_SRC	=	ft_lstnew.c \
				ft_lstadd_front.c \
				ft_lstsize.c \
				ft_lstlast.c \
				ft_lstadd_back.c \
				ft_lstdelone.c \
				ft_lstclear.c \
				ft_lstiter.c \
				ft_lstmap.c
			
BONUS_OBJS	=	$(BONUS_SRC:.c=.o)

all: ${NAME}

${NAME}: ${OBJ}
	${LIBC} ${NAME} ${OBJ}

$(OBJ):		| $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
				$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH):
				mkdir $(OBJ_PATH)

bonus: ${OBJS} ${BONUS_OBJS}
	${LIBC} ${NAME} ${OBJS} ${BONUS_OBJS}

clean:
	${RM} ${OBJS} ${BONUS_OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all
