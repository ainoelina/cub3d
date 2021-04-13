# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: avuorio <avuorio@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2021/03/01 09:11:19 by avuorio       #+#    #+#                  #
#    Updated: 2021/04/12 20:58:58 by avuorio       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		= cub3d

CC 			= clang
CFLAGS		= -O3 -Wall -Werror -Wextra

MLX			= MLX
MLX_FLAGS	= -lmlx -framework OpenGL -framework AppKit

HEADER		= cub3d.h

SRCS		= cub3d.c \
				init.c checks.c actions.c errors.c utils.c \
				gnl.c gnl_utils.c \
				parse.c parse_map.c parse_position.c \
				parse_texture.c parse_screen.c parse_sprite.c \
				move.c raycast.c draw.c

# FILES		= $(addprefix srcs/, $(SRCS))

OBJS		= $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) -L $(MLX) $(MLX_FLAGS) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)