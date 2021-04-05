# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: avuorio <avuorio@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2021/03/01 09:11:19 by avuorio       #+#    #+#                  #
#    Updated: 2021/03/30 14:31:17 by avuorio       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		= cub3d

CC 			= clang
CFLAGS		= -O3 -Wall -Werror -Wextra

MLX			= MLX
MLX_FLAGS	= -lmlx -framework OpenGL -framework AppKit

HEADER		= cub3d.h

SRCS		= cub3d.c \
				init.c \
				parse.c parse_win.c parse_texture.c parse_map.c parse_sprites.c\
				handle_textures.c \
				raycast.c draw.c \
				sprites.c \
				checks.c \
				position.c \
				keys.c \
				close.c \
				utils.c \
				gnl/gnl.c gnl/gnl_utils.c \
				2dmap.c

FILES		= $(addprefix srcs/, $(SRCS))

OBJS		= $(FILES:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) -L $(MLX) $(MLX_FLAGS) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)