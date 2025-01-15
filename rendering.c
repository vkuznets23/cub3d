#include "cub3d.h"

mlx_texture_t	*get_texture(t_mlx *mlx, int flag)
{
	mlx->ray->ray_angle = nor_angle(mlx->ray->ray_angle);
	if (flag == 0)
	{
		if (mlx->ray->ray_angle > M_PI / 2
			&& mlx->ray->ray_angle < 3 * (M_PI / 2))
			return (mlx->textures->east);
		else
			return (mlx->textures->west);
	}
	else
	{
		if (mlx->ray->ray_angle > 0 && mlx->ray->ray_angle < M_PI)
			return (mlx->textures->south);
		else
			return (mlx->textures->north);
	}
}

void	draw_floor_ceiling(t_mlx *mlx, int ray, int top_px, int bottom_px)
{
	int		i;
	int		c;

	i = bottom_px;
	c = get_rgb(mlx->dt->ff_c[0], mlx->dt->ff_c[1], mlx->dt->ff_c[1], 255);
	while (i < SCREEN_HEIGHT)
		my_mlx_pixel_put(mlx, ray, i++, c);
	i = 0;
	c = get_rgb(mlx->dt->cc_c[0], mlx->dt->cc_c[1], mlx->dt->cc_c[1], 255);
	while (i < top_px)
		my_mlx_pixel_put(mlx, ray, i++, c);
}

double	get_x_o(mlx_texture_t *texture, t_mlx *mlx)
{
	double	x_o;

	if (mlx->ray->flag == 1)
		x_o = (int)fmodf((mlx->ray->horiz_x * (texture->width / TILE_SIZE)),
				texture->width);
	else
		x_o = (int)fmodf((mlx->ray->vert_y * (texture->width / TILE_SIZE)),
				texture->width);
	return (x_o);
}

void	draw_wall(t_mlx *mlx, int t_pix, int b_pix, double wall_h)
{
	double			x_o;
	double			y_o;
	mlx_texture_t	*texture;
	uint32_t		*arr;
	double			factor;

	texture = get_texture(mlx, mlx->ray->flag);
	arr = (uint32_t *)texture->pixels;
	factor = (double)texture->height / wall_h;
	x_o = get_x_o(texture, mlx);
	y_o = (t_pix - (SCREEN_HEIGHT / 2) + (wall_h / 2)) * factor;
	if (y_o < 0)
		y_o = 0;
	while (t_pix < b_pix)
	{
		my_mlx_pixel_put(mlx, mlx->ray->index, t_pix,
			reverse_bytes(arr[(int)y_o * texture->width + (int)x_o]));
		y_o += factor;
		t_pix++;
	}
}

void	render_cub(t_mlx *mlx, int ray)
{
	double	wall_h;
	double	bottom_px;
	double	top_px;

	mlx->ray->distance *= cos(nor_angle(mlx->ray->ray_angle - mlx->player->angle));
	wall_h = (TILE_SIZE / mlx->ray->distance) * ((SCREEN_WIDTH / 2) / tan(mlx->player->fov / 2));
	bottom_px = (SCREEN_HEIGHT / 2) + (wall_h / 2);
	top_px = (SCREEN_HEIGHT / 2) - (wall_h / 2);
	if (bottom_px > SCREEN_HEIGHT)
		bottom_px = SCREEN_HEIGHT;
	if (top_px < 0)
		top_px = 0;
	mlx->ray->index = ray;
	draw_wall(mlx, top_px, bottom_px, wall_h);
	draw_floor_ceiling(mlx, ray, top_px, bottom_px);
}
