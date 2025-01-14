#include "cub3d.h"

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
    mlx->ray->horiz_x = h_x;
	mlx->ray->horiz_y = h_y;
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
    mlx->ray->vert_x = v_x;
	mlx->ray->vert_y = v_y;
    // Return the Euclidean distance
    return sqrt(pow(v_x - mlx->player->player_x, 2) + pow(v_y - mlx->player->player_y, 2));
}

//set rays in FOV 
void    cast_rays(t_mlx *mlx)
{
    int     ray;
    double   h_inter;
    double   v_inter;

    ray = 0;

    // Start with the leftmost ray angle
    mlx->ray->ray_angle = mlx->player->angle - (mlx->player->fov / 2);
    while (ray < SCREEN_WIDTH)
    {
        mlx->ray->flag = 0;
        //FIND HORRIZONTAL AND VERTICAL INTERSECTION with walls
        h_inter = get_h_inter(mlx, nor_angle(mlx->ray->ray_angle));
        v_inter = get_v_inter(mlx, nor_angle(mlx->ray->ray_angle));

        // Choose the closest intersection (horizontal or vertical)
        if (v_inter <= h_inter)
            mlx->ray->distance = v_inter;
        else
        {
            mlx->ray->distance = h_inter;
            mlx->ray->flag = 1;
        }

         // Render the wall based on the distance
        render_cub(mlx, ray); //need to do that function!!
        ray++;
        mlx->ray->ray_angle += (mlx->player->fov / SCREEN_WIDTH);
    }
}
