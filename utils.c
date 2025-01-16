#include "cub3d.h"

int	get_rgb(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a << 0);
}

int	reverse_bytes(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	if (x < 0)
		return ;
	else if (x >= SCREEN_WIDTH)
		return ;
	if (y < 0)
		return ;
	else if (y >= SCREEN_HEIGHT)
		return ;
	mlx_put_pixel(mlx->img, x, y, color);
}

int	count_lines(char **map)
{
	int	count;

	count = 0;
	while (map[count] != NULL)
		count++;
	return (count);
}

void	find_n_position(t_data *dt)
{
	int	y;
	int	x;

	y = 0;
	while (dt->map[y] != NULL)
	{
		x = 0;
		while (dt->map[y][x] != '\0')
		{
			if (dt->map[y][x] == 'N' || dt->map[y][x] == 'S'
				|| dt->map[y][x] == 'W' || dt->map[y][x] == 'E')
			{
				dt->pl_x = x + 1;
				dt->pl_y = y + 1;
			}
			x++;
		}
		y++;
	}
}
