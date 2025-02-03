/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuznets <vkuznets@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:50:26 by vkuznets          #+#    #+#             */
/*   Updated: 2025/02/03 09:48:45 by vkuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * Selects the correct texture based on the ray's angle and the flag passed
 *
 * @mlx Pointer to the main game structure containing player and map data.
 * @flag Determans east/west or north/south position
 */
mlx_texture_t	*get_texture(t_mlx *mlx, int flag)
{
	mlx->ray->ray_angle = norm_angle(mlx->ray->ray_angle);
	if (flag == 0)
	{
		if (mlx->ray->ray_angle > M_PI / 2
			&& mlx->ray->ray_angle < 3 * (M_PI / 2))
			return (mlx->textures->west);
		else
			return (mlx->textures->east);
	}
	else
	{
		if (mlx->ray->ray_angle > 0 && mlx->ray->ray_angle < M_PI)
			return (mlx->textures->south);
		else
			return (mlx->textures->north);
	}
}

/**
 * Calculates the horizontal intersection of a ray with the map grid.
 *
 * It calculates the color for the floor and ceiling using get_rgb for the
 * respective color components (ff_c for floor and cc_c for ceiling).
 * The function draws pixels from the top_px (ceiling) to the middle of the
 * screen, and from the middle to the bottom_px (floor), filling the space with 
 * the corresponding ceiling or floor color.
 *
 * @mlx Pointer to the main game structure containing player and map data.
 * @ray The column index on the screen, representing the current rendering ray.
 * @top_px The pixel position for the top of the wall slice on the screen. 
 * @bottom_px The pixel position for the bottom of the wall slice on the screen
 */
void	draw_floor_ceiling(t_mlx *mlx, int ray, int top_px, int bottom_px)
{
	int		i;
	int		c;

	i = bottom_px;
	c = get_rgb(mlx->dt->ff_c[0], mlx->dt->ff_c[1], mlx->dt->ff_c[2], 255);
	while (i < SCREEN_HEIGHT)
		my_mlx_pixel_put(mlx, ray, i++, c);
	i = 0;
	c = get_rgb(mlx->dt->cc_c[0], mlx->dt->cc_c[1], mlx->dt->cc_c[2], 255);
	while (i < top_px)
		my_mlx_pixel_put(mlx, ray, i++, c);
}

/**
 * Computes the X-offset on the texture that corresponds to the current
 * position of the ray hitting the wall.
 *
 * if mlx->ray->flag == 1 (vertical ray), it calculates the X-offset based on
 * the horiz_x coordinate. Otherwise, it uses the vert_y coordinate for
 * horizontal rays. The function uses the modulo operation (fmodf) to ensure
 * the X-coordinate stays within the bounds of the texture width, adjusting it
 * to repeat the texture appropriately
 *
 * @mlx Pointer to the main game structure containing player and map data.
 * @texture Pointer to a struct that holds all data about textures
 */
double	get_x_offset(mlx_texture_t *texture, t_mlx *mlx)
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

/**
 * This function is responsible for rendering a vertical wall column
 * on the screen
 *
 * The function calculates the texture offset (x_o and y_o) using
 * the get_x_offset function to properly map the texture to the wall's height.
 * The y_o value is used to sample the texture, and the pixel colors are placed
 * on the screen, creating a vertical strip representing the wall. The factor
 * determines the scaling of the texture to match the wall height.
 *
 * @mlx Pointer to the main game structure containing player and map data.
 * @t_pix and b_pix represent the top/bottom px positions for the wall's height
 * @wall_h Height of the wall. It defines how tall the wall will appear
 * based on the distance from the player to the wall.
*/
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
	x_o = get_x_offset(texture, mlx);
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

/**
 * This function handles the entire rendering process for a single ray.
 *
 * First, it adjusts the ray's distance based on the player's view angle.
 * Then calculate wall_h based on the distance of the ray and the fov, then
 * top_px and bottom_px help to determin where the wall starts and ends
 * on the screen. If checks ensure the wall stays within the screen bounds,
 * clipping it if necessary. Finally, it calls draw_wall to render the wall
 * and draw_floor_ceiling to render the floor and ceiling.
 *
 * @mlx Pointer to the main game structure containing player and map data.
 * @ray The column index on the screen, representing the current rendering ray.
*/
void	render_cub(t_mlx *mlx, int ray)
{
	double	wall_h;
	double	bottom_px;
	double	top_px;

	mlx->ray->distance *= cos(norm_angle(mlx->ray->ray_angle
				- mlx->player->angle));
	wall_h = (TILE_SIZE / mlx->ray->distance) * ((SCREEN_WIDTH / 2)
			/ tan(mlx->player->fov / 2));
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
