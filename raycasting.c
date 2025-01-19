#include "cub3d.h"

/**
 * Calculates the horizontal intersection of a ray with the map grid.
 *
 * This function determines the first horizontal grid intersection for a ray
 * and steps through successive grid lines until it encounters a wall. It uses
 * the ray angle to calculate the step size and checks for wall collisions
 * along the way. The intersection coordinates are stored in the `mlx->ray`
 * structure, and the distance from the player to the intersection is returned.
 *
 * @mlx Pointer to the main game structure containing player and map data.
 * @angl The angle of the ray, normalized to [0, 2π].
 * @The distance from the player to the horizontal intersection.
 */
static float	get_h_inter(t_mlx *mlx, float angl)
{
	float	y_step;
	float	x_step;
	float	h_x;
	float	h_y;
	int		pixel;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angl);
	h_y = floor(mlx->player->player_y / TILE_SIZE) * TILE_SIZE;
	pixel = set_ray_step(angl, &h_y, &y_step, 1);
	h_x = mlx->player->player_x + (h_y - mlx->player->player_y) / tan(angl);
	if ((get_ray_direction(angl, 'y') && x_step > 0)
		|| (!get_ray_direction(angl, 'y') && x_step < 0))
		x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, mlx))
	{
		h_x += x_step;
		h_y += y_step;
	}
	mlx->ray->horiz_x = h_x;
	mlx->ray->horiz_y = h_y;
	return (sqrt(pow(h_x - mlx->player->player_x, 2)
			+ pow(h_y - mlx->player->player_y, 2)));
}

/**
 * Calculates the vertical intersection of a ray with the map grid.
 *
 * This function determines the first vertical grid intersection for a ray 
 * and steps through successive grid lines until it encounters a wall. It uses 
 * the ray angle to calculate the step size and checks for wall collisions 
 * along the way. The intersection coordinates are stored in the `mlx->ray` 
 * structure, and the distance from the player to the intersection is returned.
 *
 * @mlx Pointer to the main game structure containing player and map data.
 * @angl The angle of the ray, normalized to [0, 2π].
 * @return The distance from the player to the vertical intersection.
 */
static float	get_v_inter(t_mlx *mlx, float angl)
{
	float	x_step;
	float	y_step;
	float	v_x;
	float	v_y;
	int		pixel;

	x_step = TILE_SIZE;
	y_step = TILE_SIZE * tan(angl);
	v_x = floor(mlx->player->player_x / TILE_SIZE) * TILE_SIZE;
	pixel = set_ray_step(angl, &v_x, &x_step, 0);
	v_y = mlx->player->player_y + (v_x - mlx->player->player_x) * tan(angl);
	if ((get_ray_direction(angl, 'x') && y_step < 0)
		|| (!get_ray_direction(angl, 'x') && y_step > 0))
		y_step *= -1;
	while (wall_hit(v_x - pixel, v_y, mlx))
	{
		v_x += x_step;
		v_y += y_step;
	}
	mlx->ray->vert_x = v_x;
	mlx->ray->vert_y = v_y;
	return (sqrt(pow(v_x - mlx->player->player_x, 2)
			+ pow(v_y - mlx->player->player_y, 2)));
}

/**
 * Casts rays from the player's position to render the scene.
 *
 * This function simulates a field of view by casting rays from the player's
 * position at angles spanning the player's FOV. For each ray, it calculates
 * both horizontal and vertical intersections with the map grid and determines
 * the closer one. The calculated distance and intersection data are used to
 * render vertical strips representing walls on the screen.
 *
 * @mlx Pointer to the main game structure containing player, map, and ray data.
 */
void	cast_rays(t_mlx *mlx)
{
	int		ray;
	double	h_inter;
	double	v_inter;

	ray = 0;
	mlx->ray->ray_angle = mlx->player->angle - (mlx->player->fov / 2);
	while (ray < SCREEN_WIDTH)
	{
		mlx->ray->flag = 0;
		h_inter = get_h_inter(mlx, norm_angle(mlx->ray->ray_angle));
		v_inter = get_v_inter(mlx, norm_angle(mlx->ray->ray_angle));
		if (v_inter <= h_inter)
			mlx->ray->distance = v_inter;
		else
		{
			mlx->ray->distance = h_inter;
			mlx->ray->flag = 1;
		}
		render_cub(mlx, ray);
		ray++;
		mlx->ray->ray_angle += (mlx->player->fov / SCREEN_WIDTH);
	}
}
