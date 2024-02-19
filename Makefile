# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/08 12:03:00 by jqueijo-          #+#    #+#              #
#    Updated: 2024/02/19 10:20:09 by jqueijo-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRC = window.c \

CC = cc
MINILIBX_FLAGS= -Lminilibx-linux -l:libmlx_Linux.a -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
CFLAGS = -Wall -Werror -Wextra

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MINILIBX_FLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all, bonus, clean, fclean, re
