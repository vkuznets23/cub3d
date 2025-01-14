#include "cub3d.h"

//so we need this one to prevent overflow kinda? to be in the range of 360 degree
float	nor_angle(float angle)	// normalize the angle
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

//unit_circle checks which direction the ray is moving:
//'x': Is the ray moving down? (Top half of the unit circle: 0 to π)
//'y': Is the ray moving left? (Left half of the unit circle: π/2 to 3π/2)
//It only tells the general direction of the ray (up/down or left/right) without modifying anything.
int	unit_circle(float angle, char c)	// check the unit circle
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

// Adjusts the initial intersection and step direction based on the ray's direction and grid type (horizontal or vertical)
//insimlple words: Ensures the ray starts at the correct initial grid line (horizontal or vertical)!!
int inter_check(float angle, float *inter, float *step, int is_horizon)
{
    //This range corresponds to rays that are moving in the top half of the unit circle (UP DOWN) -> horizontal lines
    if (is_horizon)
    {
        if (angle > 0 && angle < M_PI)
        {
            *inter += TILE_SIZE;
            return (-1); 
        }
        //if its not in the right range we flip the direction of the step
        *step *= -1;
    }
    //adjusts the ray's position as it moves across vertical grid lines (right and left)
    else //if its 0 we are working with vertical raycasting
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

//checks if the ray has hit a wall at the current position
//it hasn't hit a wall, the ray continues to move along the grid lines
int	wall_hit(float x, float y, t_mlx *mlx)	// check the wall hit
{
	int		x_m;
	int		y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor (x / TILE_SIZE); // get the x position in the map
	y_m = floor (y / TILE_SIZE); // get the y position in the map
	if ((y_m >= mlx->dt->h_map || x_m >= mlx->dt->w_map))
		return (0);
	if (mlx->dt->map[y_m] && x_m <= (int)ft_strlen(mlx->dt->map[y_m]))
		if (mlx->dt->map[y_m][x_m] == '1')
			return (0);
	return (1);
}