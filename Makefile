# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/08 12:03:00 by jqueijo-          #+#    #+#              #
#    Updated: 2024/02/28 14:34:16 by jqueijo-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRC =  main.c \
		aux_utils.c \
		# equation.c \
		# window.c \

CC = cc
MINILIBX_FLAGS= -Lminilibx-linux -l:libmlx_Linux.a -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
CFLAGS =

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MINILIBX_FLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

real: CFLAGS += -Wall -Werror -Wextra
real: re

.PHONY: all, bonus, clean, fclean, re
