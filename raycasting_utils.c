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
float	norm_angle(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

/**
 * Determines the direction of the ray along the X or Y axis.
 *
 * Based on the given angle, this function determines whether the ray is moving 
 * in a positive or negative direction along the specified axis (X or Y).
 * 
 * For the X axis:
 * - Returns 1 if the ray is moving downwards (positive Y direction).
 * - Returns 0 if the ray is moving upwards (negative Y direction).
 *
 * For the Y axis:
 * - Returns 1 if the ray is moving left (negative X direction).
 * - Returns 0 if the ray is moving right (positive X direction).
 **
 * This is used to determine how the ray interacts with the grid
 * and to calculate the correct initial intersection and step size for the
 * raycasting algorithm.
 *
 * @angle The angle in radians.
 * @c A character ('x' or 'y') indicating the axis to check.
 * @return 1 if the ray moves positively along the specified axis, 0 otherwise.
 */
int	get_ray_direction(float angle, char c)
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
 ** Sets the starting point and step direction for ray traversal.
 *
 * Adjusts the initial intersection position and step size based on the ray's
 * angle and direction (up/down or left/right). Determines which grid cell 
 * to check for walls during ray traversal.
 *
 * In simple terms:
 * The function helps to determine:
 * - Where the ray intersects the first grid line.
 * - In which direction the ray will move.
 * - Which grid cell to check for a wall: before or after the intersection point.
 *
 * @angle The angle of the ray in radians.
 * @inter Pointer to the initial intersection coordinate (x or y).
 * @step Pointer to the step size (x or y).
 * @is_horizon Set to 1 for horizontal intersections, 0 for vertical.
 * @return -1 for upward or leftward direction, 1 otherwise.
 */
int	set_ray_step(float angle, float *inter, float *step, int is_horizon)
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
