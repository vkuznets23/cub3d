# Variables
NAME = cub3d

# Paths
MLX42_DIR = ./MLX42
LIBFT_DIR = ./libft
MLX42_BUILD_DIR = $(MLX42_DIR)/build
MLX42_INCLUDE_DIR = $(MLX42_DIR)/include
GLFW_LIB = $(MLX42_BUILD_DIR)/_deps/glfw-build/src/libglfw3.a
LIBFT = $(LIBFT_DIR)/libft.a
PARS_DIR = ./parsing

SRCS = main.c moving.c utils.c raycasting.c raycasting_utils.c rendering.c exit.c initialization.c \
	$(PARS_DIR)/capture_data.c \
	$(PARS_DIR)/debug.c \
	$(PARS_DIR)/norm_map.c \
	$(PARS_DIR)/parse_file.c \
	$(PARS_DIR)/parsing_utils.c \
	$(PARS_DIR)/color.c \
	$(PARS_DIR)/pars_clean.c \
	$(PARS_DIR)/validate_map.c

OBJS = $(SRCS:.c=.o)

# Compiler and flags
CC = cc
CFLAGS = -I$(MLX42_INCLUDE_DIR) -I$(LIBFT_DIR)  # Include libft headers
#LDFLAGS = -L./MLX42/build -lMLX42 -lglfw -ldl -lm $(LIBFT)
LDFLAGS = $(MLX42_BUILD_DIR)/libmlx42.a -ldl -lglfw -pthread -lm -lX11 $(LIBFT)


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
