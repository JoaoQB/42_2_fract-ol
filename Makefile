# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/08 12:03:00 by jqueijo-          #+#    #+#              #
#    Updated: 2024/02/09 15:50:04 by jqueijo-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = window

SRC = window.c \

CC = cc
minilibx_flags= -Lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz
mlx= libmlx_Linux.a
CFLAGS = -Wall -Werror -Wextra

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX) $(minilibx_flags)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all, bonus, clean, fclean, re
