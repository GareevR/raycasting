# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frariel <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/21 17:19:14 by frariel           #+#    #+#              #
#    Updated: 2021/03/04 22:30:08 by frariel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = gcc

FN_NAMES = main.c \
			check_valid.c \
			set_player.c \
			sprite_count.c \
			parser.c \
			set_textures.c \
			set_flr_ceil.c \
			set_values.c \
			movement.c \
			calculations.c \
			check_values.c \
			drawing.c \
			events.c \
			parse_map.c \
			sprites.c \
			screenshot.c

FN_NAMES_O= $(FN_NAMES:.c=.o)

GNL_C = get_next_line.c \
		get_next_line_utils.c

GNL_O = $(GNL_C:.c=.o)

all: $(NAME)

$(NAME): $(FN_NAMES_O)
		cd ./libft && make && mv libft.a .. && make clean && cd .. && \
		cd ./mlx && make && mv libmlx.dylib .. && make clean && cd .. && \
		$(CC) -Wall -Wextra -Werror -Imlx -c $(FN_NAMES) $(GNL_C) && \
		$(CC) $(FN_NAMES_O) $(GNL_O) libft.a -Lmlx -lmlx -framework OpenGL \
		-framework AppKit -o $(NAME)

clean:
		/bin/rm -f $(FN_NAMES_O) $(GNL_O)

fclean: clean
		/bin/rm -f $(NAME) libft.a libmlx.dylib

re: fclean all
