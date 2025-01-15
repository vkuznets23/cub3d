#include "cub3d.h"

/**
 * Normalizes an angle to the range [0, 2π].
 *
 * Ensures the angle is wrapped within a full circle, adjusting it if it is
 * less than 0 or greater than 2π.
 *
 * @angle The angle in radians.
 * @return The normalized angle in radians.
 */
float	nor_angle(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

/**
 * Determines the ray's quadrant for x or y direction.
 *
 * Based on the given angle, determines whether the ray is moving in the
 * positive or negative direction along the x or y-axis.
 *
 * @angle The angle in radians.
 * @c A character ('x' or 'y') indicating the axis to check.
 * @return 1 if the ray moves positively along the specified axis, 0 otherwise.
 */
int	unit_circle(float angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}

/**
 * Adjusts initial intersection and step values based on ray direction.
 *
 * For horizontal or vertical intersections, adjusts the starting intersection 
 * position and step size depending on the angle of the ray. It also determines 
 * the direction to step in.
 *
 * @angle The angle of the ray in radians.
 * @inter Pointer to the initial intersection coordinate (x or y).
 * @step Pointer to the step size (x or y).
 * @is_horizon Set to 1 for horizontal intersections, 0 for vertical.
 * @return -1 for upward or leftward direction, 1 otherwise.
 */
int	inter_check(float angle, float *inter, float *step, int is_horizon)
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}


/**
 * Checks whether a given map coordinate is a wall.
 *
 * Converts world coordinates to map grid coordinates and checks if the position
 * corresponds to a wall ('1') in the map data. Ensures the position is within
 * bounds before accessing the map array.
 *
 * @x The x-coordinate in the game world.
 * @y The y-coordinate in the game world.
 * @mlx Pointer to the main game structure containing map data.
 * @return 0 if the position is a wall or out of bounds, 1 otherwise.
 */
int	wall_hit(float x, float y, t_mlx *mlx)
{
	int		x_m;
	int		y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor (x / TILE_SIZE);
	y_m = floor (y / TILE_SIZE);
	if ((y_m >= mlx->dt->h_map || x_m >= mlx->dt->w_map))
		return (0);
	if (mlx->dt->map[y_m] && x_m <= (int)ft_strlen(mlx->dt->map[y_m]))
		if (mlx->dt->map[y_m][x_m] == '1')
			return (0);
	return (1);
}
