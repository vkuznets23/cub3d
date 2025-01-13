#include "cub3d.h"

static int inter_check(float angle, float *inter, float *step, int is_horizon)
{
    //This range corresponds to rays that are moving in the top half of the unit circle 
    if (is_horizon) //its horizontal if its 1 (here we check horizonta grid lines)
    {
        if (angle > 0 && angle < M_PI)
        {
            *inter += TILE_SIZE;
            return (-1); //This tells the function to adjust the vertical step 
        }
        //if its not int he right range we flip the direction of the step
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
static int	wall_hit(float x, float y, t_mlx *mlx)	// check the wall hit
{
	int		x_m;
	int		y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor (x / TILE_SIZE); // get the x position in the map
	y_m = floor (y / TILE_SIZE); // get the y position in the map
	if ((y_m >= mlx->map->h_map || x_m >= mlx->map->w_map))
		return (0);
	if (mlx->map->map[y_m] && x_m <= (int)ft_strlen(mlx->map->map[y_m]))
		if (mlx->map->map[y_m][x_m] == '1')
			return (0);
	return (1);
}

//lets calculate distance from players position to the nearest horiz wall
//angl: This is the angle at which the ray is being cast
static float   get_h_inter(t_mlx *mlx, float angl)
{
    float   y_step;
    float   x_step;
    float   h_x;
    float   h_y;
    int     pixel;

    y_step = TILE_SIZE; // cos angle doesnt change when u go forward and back
    x_step = TILE_SIZE / tan(angl); // here it might change -> This is the amount the ray moves horizontally per vertical step

    //This calculates the y position of the first horizontal grid line that the ray intersects.
    h_y = floor(mlx->player->player_y / TILE_SIZE) * TILE_SIZE;
    pixel = inter_check(angl, &h_y, &y_step, 1);
    //This calculates the x position where the ray first intersects a horizontal line.
    h_x = mlx->player->player_x + (h_y - mlx->player->player_y) / tan(angl);
    if ((unit_circle(angl, 'y') && x_step > 0) || (!unit_circle(angl, 'y') && x_step < 0))
        x_step *= -1;
    while (wall_hit(h_x, h_y - pixel, mlx))  // check the wall hit with the pixel value
    {
        h_x += x_step;
        h_y += y_step;
    }
    //This calculates the Euclidean distance from the player's position 
    //(mlx->ply->plyr_x, mlx->ply->plyr_y) to the final intersection point (h_x, h_y).
    //The formula sqrt(a^2 + b^2) is used to calculate the straight-line distance between
    //two points (the player's position and the intersection point)
    return (sqrt(pow(h_x - mlx->player->player_x, 2) + pow(h_y - mlx->player->player_y, 2)));
}

static float get_v_inter(t_mlx *mlx, float angl)
{
    float x_step;
    float y_step;
    float v_x;
    float v_y;
    int pixel;

    x_step = TILE_SIZE;  // same as for y_step
    y_step = TILE_SIZE * tan(angl);  // Adjust the vertical step

    v_x = floor(mlx->player->player_x / TILE_SIZE) * TILE_SIZE;  // Start of the vertical line
    pixel = inter_check(angl, &v_x, &x_step, 0);  // Get vertical intersection adjustment
    v_y = mlx->player->player_y + (v_x - mlx->player->player_x) * tan(angl);  // Adjust y position

    if ((unit_circle(angl, 'x') && y_step < 0) || (!unit_circle(angl, 'x') && y_step > 0))
        y_step *= -1;

    while (wall_hit(v_x - pixel, v_y, mlx))  // Check for a wall at the vertical position
    {
        v_x += x_step;
        v_y += y_step;
    }

    // Return the Euclidean distance
    return sqrt(pow(v_x - mlx->player->player_x, 2) + pow(v_y - mlx->player->player_y, 2));
}

///////
static void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)	// put the pixel
{
	if (x < 0) // check the x position
		return ;
	else if (x >= SCREEN_WIDTH)
		return ;
	if (y < 0) // check the y position
		return ;
	else if (y >= SCREEN_HEIGHT)
		return ;
	mlx_put_pixel(mlx->img, x, y, color); // put the pixel
}

void	draw_floor_ceiling(t_mlx *mlx, int ray, int t_pix, int b_pix)	// draw the floor and the ceiling
{
	int		i;
	int		c;

	i = b_pix;
	while (i < SCREEN_HEIGHT)
		my_mlx_pixel_put(mlx, ray, i++, 0xB99470FF); // floor
	i = 0;
	while (i < t_pix)
		my_mlx_pixel_put(mlx, ray, i++, 0x89CFF3FF); // ceiling
}

int	get_color(t_mlx *mlx, int flag)	// get the color of the wall
{
	mlx->ray->ray_angle = nor_angle(mlx->ray->ray_angle); // normalize the angle
	if (flag == 0)
	{
		if (mlx->ray->ray_angle > M_PI / 2 && mlx->ray->ray_angle < 3 * (M_PI / 2))
			return (0xB5B5B5FF); // west wall
		else
			return (0xB5B5B5FF); // east wall
	}
	else
	{
		if (mlx->ray->ray_angle > 0 && mlx->ray->ray_angle < M_PI)
			return (0xF5F5F5FF); // south wall
		else
			return (0xF5F5F5FF); // north wall
	}
}

void	draw_wall(t_mlx *mlx, int ray, int t_pix, int b_pix)	// draw the wall
{
	int color;

	color = get_color(mlx, mlx->ray->flag);
	while (t_pix < b_pix)
		my_mlx_pixel_put(mlx, ray, t_pix++, color);
}

void	render_wall(t_mlx *mlx, int ray)	// render the wall
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	mlx->ray->distance *= cos(nor_angle(mlx->ray->ray_angle - mlx->player->angle)); // fix the fisheye
	wall_h = (TILE_SIZE / mlx->ray->distance) * ((SCREEN_WIDTH / 2) / tan(mlx->player->fov / 2)); // get the wall height
	b_pix = (SCREEN_HEIGHT / 2) + (wall_h / 2); // get the bottom pixel
	t_pix = (SCREEN_HEIGHT / 2) - (wall_h / 2); // get the top pixel
	if (b_pix > SCREEN_HEIGHT) // check the bottom pixel
		b_pix = SCREEN_HEIGHT;
	if (t_pix < 0) // check the top pixel
		t_pix = 0;
	draw_wall(mlx, ray, t_pix, b_pix); // draw the wall
	draw_floor_ceiling(mlx, ray, t_pix, b_pix); // draw the floor and the ceiling
}
//////



void    cast_rays(t_mlx *mlx)
{
    int     ray;
    float   h_inter;
    float   v_inter;

    ray = 0;

    // Start with the leftmost ray angle
    mlx->ray->ray_angle = mlx->player->angle - (mlx->player->fov / 2);
    while (ray < SCREEN_WIDTH)
    {
        mlx->ray->flag = 0;
        //FIND HORRIZONTAL AND VERTICAL INTERSECTION
        h_inter = get_h_inter(mlx, nor_angle(mlx->ray->ray_angle));
        v_inter = get_v_inter(mlx, nor_angle(mlx->ray->ray_angle));

        // Choose the closest intersection (horizontal or vertical)
        if (v_inter < h_inter)
        {
            mlx->ray->distance = v_inter;
            mlx->ray->flag = 1;  // Indicate that this is a vertical intersection
        }
        else
        {
            mlx->ray->distance = h_inter;
            mlx->ray->flag = 0;  // Indicate that this is a horizontal intersection
        }

         // Render the wall based on the distance
        render_wall(mlx, ray); //need to do that function!!
        ray++;
        mlx->ray->ray_angle += (mlx->player->fov / SCREEN_WIDTH);
    }
}
