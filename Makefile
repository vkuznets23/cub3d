# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkuznets <vkuznets@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/20 13:25:57 by vkuznets          #+#    #+#              #
#    Updated: 2025/01/20 13:48:33 by vkuznets         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
NAME = cub3d

# Paths
MLX42_DIR = ./MLX42
LIBFT_DIR = ./libft
MLX42_BUILD_DIR = $(MLX42_DIR)/build
MLX42_INCLUDE_DIR = $(MLX42_DIR)/include
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_OBJ = $(LIBFT_DIR)/*.o

PARS_DIR = ./parsing
EXEC_DIR = ./execution

SRCS = main.c \
	$(EXEC_DIR)/moving.c \
	$(EXEC_DIR)/utils.c \
	$(EXEC_DIR)/raycasting.c \
	$(EXEC_DIR)/raycasting_utils.c \
	$(EXEC_DIR)/rendering.c \
	$(EXEC_DIR)/exit.c \
	$(EXEC_DIR)/initialization.c \
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
CFLAGS = -I$(MLX42_INCLUDE_DIR) -I$(LIBFT_DIR) -Wall -Wextra -Werror  # Include libft headers
#LDFLAGS = -L./MLX42/build -lMLX42 -lglfw -ldl -lm $(LIBFT)
LDFLAGS = $(MLX42_BUILD_DIR)/libmlx42.a -ldl -lglfw -pthread -lm -lX11 $(LIBFT)


# Targets
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) | $(MLX42_BUILD_DIR)/libmlx42.a
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $(NAME)

# Ensure MLX42 is built first before linking
$(MLX42_BUILD_DIR)/libmlx42.a:
	cmake $(MLX42_DIR) -B $(MLX42_BUILD_DIR) && make -C $(MLX42_BUILD_DIR) -j4 && cd ..

# Compile object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Build libft.a
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Clean object files
clean:
	rm -f $(OBJS) $(LIBFT_OBJ)
	rm -rf $(MLX42_BUILD_DIR) $(LIBFT)

# Clean object files and libft.a
fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re $(LIBFT)
