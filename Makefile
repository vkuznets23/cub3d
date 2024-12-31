CC = gcc
CFLAGS = -I./MLX42/include
LDFLAGS = -L./MLX42/build -lMLX42 -lglfw -ldl -lm
SRC = main.c
OUT = cub3d

all:
	$(CC) $(SRC) $(CFLAGS) $(LDFLAGS) -o $(OUT)

clean:
	rm -f $(OUT)

