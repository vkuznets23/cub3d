# Variables
NAME = cub3d
SRCS = main.c moving.c utils.c raycasting.c raycasting_utils.c rendering.c exit.c \
       ./parsing/capture_data.c ./parsing/debug.c ./parsing/norm_map.c ./parsing/parse_file.c ./parsing/parsing_utils.c ./parsing/color.c ./parsing/pars_clean.c ./parsing/validate_map.c

OBJS = $(SRCS:.c=.o)

# Paths
MLX42_DIR = ./MLX42
LIBFT_DIR = ./libft
MLX42_BUILD_DIR = $(MLX42_DIR)/build
MLX42_INCLUDE_DIR = $(MLX42_DIR)/include
GLFW_LIB = $(MLX42_BUILD_DIR)/_deps/glfw-build/src/libglfw3.a
LIBFT = $(LIBFT_DIR)/libft.a

# Compiler and flags
CC = cc
CFLAGS = -I$(MLX42_INCLUDE_DIR) -I$(LIBFT_DIR)  # Include libft headers
LDFLAGS = -L./MLX42/build -lMLX42 -lglfw -ldl -lm $(LIBFT)
#LDFLAGS = $(MLX42_BUILD_DIR)/libmlx42.a $(GLFW_LIB) -ldl -pthread -lm -lX11 $(LIBFT)


# Targets
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $(NAME)

# Compile object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Build libft.a
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Clean object files
clean:
	rm -f $(OBJS)

# Clean object files and libft.a
fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re $(LIBFT)


