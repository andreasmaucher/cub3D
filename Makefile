# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amaucher <amaucher@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/19 12:32:18 by ashojach          #+#    #+#              #
#    Updated: 2024/06/05 01:07:01 by amaucher         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler
CC = cc

# Flags
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L./mlx -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
MLX = mlx
MLX_LIB = $(MLX)/libmlx.a

# Source files
SRCS = ./src/main.c ./src/parser/parser.c ./src/gnl/gnl.c \
		./src/gnl/gnl_utils.c ./src/drawing.c ./src/keys.c ./src/minimap.c \
		./src/gnl/gnl_utils_1.c ./src/dda.c ./src/moves.c \
		./src/parser/parse_data.c ./src/parser/parse_map.c \
		./src/texture_utils.c ./src/textures.c \

# Object files
OBJS = $(SRCS:.c=.o)

# Target
NAME = cub3D

# Default target
all: $(NAME)

# Rule to build the target
$(NAME): $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

# Make minilibx
$(MLX_LIB):
	cd $(MLX) && make

# Rule to build object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJS)

# Clean rule for all generated files
fclean: clean
	rm -f $(NAME)
	cd $(MLX) && make clean

re: fclean all

# Phony targets
.PHONY: all clean fclean
