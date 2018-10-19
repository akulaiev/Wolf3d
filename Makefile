# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/07 11:21:04 by akulaiev          #+#    #+#              #
#    Updated: 2018/05/07 11:21:06 by akulaiev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

CC = gcc
CFLAGS = -Wall -Werror -Wextra

LIBFT = ./libft/libft.a

LIBFT_PATH = ./libft/
SRC_PATH = ./src/
INC_PATH = ./inc

MLX = ./minilibx_macos/libmlx.a
MLX_PATH = ./minilibx_macos/

vpath %.c $(SRC_PATH)

SOURCE = main.c raycast.c vector_operations.c \
mlx_manipulate.c raycast_help.c parser.c

O_FILES = $(addprefix $(SRC_PATH), $(SOURCE:.c=.o))

all: LIBS $(NAME) 

$(NAME): $(O_FILES)
	$(CC) $(MLX) -framework OpenGL -framework AppKit $(CFLAGS) -o $(NAME) $(O_FILES) $(LIBFT)

LIBS:
	make -C $(MLX_PATH)
	make -C $(LIBFT_PATH)

%.o: %.c $(INC_PATH)/wolf3d.h
	$(CC) $(CFLAGS) -I $(INC_PATH) -c $< -o $@

exe:
	./$(NAME) ./maps/test_map

clean:
	make -C $(LIBFT_PATH) clean
	rm -f $(O_FILES)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -f $(NAME)
	clear

norm:
	norminette $(SOURCE)

re: fclean all
