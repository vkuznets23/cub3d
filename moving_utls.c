#include "cub3d.h"

//this function sets player movement or rotation to 0 when a key is released
static void    ft_release(mlx_key_data_t keydata, t_mlx *mlx)
{
    if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
        mlx->player->left_right = 0;
    else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
        mlx->player->left_right = 0;
    else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
        mlx->player->up_down = 0;
    else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
        mlx->player->up_down = 0;
    else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_RELEASE))
        mlx->player->rotation = 0;
    else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_RELEASE))
        mlx->player->rotation = 0;
}

//processes key presses and updates the player's movement or rotation state accordingly
void    mlx_key(mlx_key_data_t keydata, void *ml)
{
    t_mlx *mlx;

    mlx = ml;
    if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS))
        //it should be proper exit with cleaning up
        exit(1);
    else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS))
        mlx->player->left_right = -1;
    else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS))
        mlx->player->left_right = 1;
    else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS))
        mlx->player->up_down = 1;
    else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS))
        mlx->player->up_down = -1;
    else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS))
        mlx->player->rotation = -1;
    else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS))
        mlx->player->rotation = 1;
    ft_release(keydata, mlx);
}

static void    move_player(t_mlx *mlx, int move_x, int move_y)
{
    int new_x;
    int new_y;
    int map_grid_x;
    int map_grid_y;

    //new position is on a grid of whole-number pixel value
    new_x = roundf(mlx->player->player_x + move_x);
    new_y = roundf(mlx->player->player_y + move_y);

    //to get the map's corresponding x and y indices.
    map_grid_x = (new_x / TILE_SIZE);
    map_grid_y = (new_y / TILE_SIZE);

    //update values
    if (mlx->map->map[map_grid_y][map_grid_x] != '1' && \
	(mlx->map->map[map_grid_y][mlx->player->player_x / TILE_SIZE] != '1' && \
	mlx->map->map[mlx->player->player_y / TILE_SIZE][map_grid_x] != '1'))
    {
        mlx->player->player_x = new_x;
        mlx->player->player_y = new_y;
    }
}

static void    rotate_player(t_mlx *mlx, int i)
{
    if (i == 1)
    {
        //causes the player to rotate in the clockwise direction
        mlx->player->angle += ROTATION_SPEED; //right
        //This ensures that once the angle exceeds 360°, it resets back to 0, preventing the angle from growing indefinitely.
        if (mlx->player->angle > 2 * M_PI)
            mlx->player->angle -= 2 * M_PI;
    }
    else
    {
        mlx->player->angle -= ROTATION_SPEED; //left
        if (mlx->player->angle < 0)
            mlx->player->angle += 2 * M_PI;
    }
}

void    hook(t_mlx *mlx, int move_x, int move_y)
{
    //rotation
    if (mlx->player->rotation == 1) //right
        rotate_player(mlx, 1);
    if (mlx->player->rotation == -1) //left
        rotate_player(mlx, 0);

    //moving left and right
    if (mlx->player->left_right == 1)   //right
    {
        move_x = -sin(mlx->player->angle) * PLAYER_SPEED;
        move_y = cos(mlx->player->angle) * PLAYER_SPEED;
    }
    if (mlx->player->left_right == -1)            // move left
    {
        move_x = sin(mlx->player->angle) * PLAYER_SPEED;
        move_y = -cos(mlx->player->angle) * PLAYER_SPEED;
    }

    //up and dow
    if (mlx->player->up_down == 1)   //up
    {
        move_x = sin(mlx->player->angle) * PLAYER_SPEED;
        move_y = cos(mlx->player->angle) * PLAYER_SPEED;
    }
    if (mlx->player->up_down == 1)   //up
    {
        move_x = -sin(mlx->player->angle) * PLAYER_SPEED;
        move_y = -cos(mlx->player->angle) * PLAYER_SPEED;
    }

    move_player(mlx, move_x, move_y);  
}