# --max-stackframe=
# Compiler
CC = cc

# Flags
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L./mlx -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

# Source files
SRCS = main.c parser.c gnl.c gnl_utils.c drawing.c keys.c

# Object files
OBJS = $(SRCS:.c=.o)

# Target
NAME = cub3D

# Default target
all: $(NAME)

# Rule to build the target
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

# Rule to build object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJS)

# Clean rule for all generated files
fclean: clean
	rm -f $(NAME)

re: fclean all

# Phony targets
.PHONY: all clean fclean