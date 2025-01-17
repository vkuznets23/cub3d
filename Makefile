# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkuznets <vkuznets@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/17 14:02:31 by vkuznets          #+#    #+#              #
#    Updated: 2025/01/17 14:02:33 by vkuznets         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project name
NAME = cub3d

# Compiler and flags
CC = cc
CFLAGS = -I./MLX42/include -I./libft -O2 -Wall -Wextra -Werror # Add optimization and warnings
LDFLAGS = -L./MLX42/build -lMLX42 -L./libft -lft \
          -framework Cocoa -framework OpenGL -framework IOKit -lpthread # macOS-specific frameworks

# Source files
SRCS = main.c moving.c utils.c raycasting.c raycasting_utils.c rendering.c exit.c \
       ./parsing/capture_data.c ./parsing/debug.c ./parsing/norm_map.c ./parsing/parse_file.c \
       ./parsing/parsing_utils.c ./parsing/color.c ./parsing/pars_clean.c ./parsing/validate_map.c

OBJS = $(SRCS:.c=.o)

# Submodules
MLX42 = MLX42
LIBFT = libft

# Default target
all: $(NAME)

# Build the project
$(NAME): $(OBJS) $(MLX42)/build/libmlx42.a $(LIBFT)/libft.a
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

# Rule for compiling .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Build MLX42 library
$(MLX42)/build/libmlx42.a:
	cmake -S $(MLX42) -B $(MLX42)/build
	cmake --build $(MLX42)/build --parallel

# Build libft library
$(LIBFT)/libft.a:
	$(MAKE) -C $(LIBFT)

# Clean object files
clean:
	rm -f $(OBJS)
	@rm -rf $(MLX42)/build
	$(MAKE) -C $(LIBFT) clean

# Full clean, including binaries
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT) fclean

# Rebuild the project
re: fclean all

.PHONY: all clean fclean re
