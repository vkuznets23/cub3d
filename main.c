#include "cub3d.h"

//setting the game
void    game_loop(void *MLX)
{
    t_mlx *mlx;

    mlx = MLX; // cast to the mlx structure cos we need void function as a hook
    mlx_delete_image(mlx->mlx_p, mlx->img);
    mlx->img = mlx_new_image(mlx->mlx_p, SCREEN_WIDTH, SCREEN_HEIGHT); //create new image
    hook(mlx, 0, 0);
    //raycasting
    cast_rays(mlx);
    mlx_image_to_window(mlx->mlx_p, mlx->img, 0, 0);
}

void    init_player(t_mlx mlx)
{
    //TILE_SIZE / 2 we need to place in the center of the tile not left edge
    mlx.player->player_x = mlx.map->pl_x * TILE_SIZE + TILE_SIZE / 2;
    mlx.player->player_y = mlx.map->pl_y * TILE_SIZE + TILE_SIZE / 2;

    //M_PI represents π
    //the result is the player's field of view in radians
    mlx.player->fov = (FOV * M_PI) / 180;
    mlx.player->angle = M_PI;

    //I WILL NEED TO CHANGE ANGLE DEPENDING ON THE N W S E
    /*
    The angle of M_PI / 2 (90 degrees) corresponds to the player facing East.
    The angle of M_PI (180 degrees) corresponds to the player facing South.
    The angle of 3 * M_PI / 2 (270 degrees) corresponds to the player facing West.
    An angle of 0 corresponds to the player facing North or 2 * M_PI if you prefer the full circle*/

    // the rest of the variables are initialized to zero by calloc
}

void    start_the_game(t_map *map_data)
{
    t_mlx mlx;

    mlx.map = map_data;
    mlx.player = ft_calloc(1, sizeof(t_player));
    mlx.ray = ft_calloc(1, sizeof(t_ray));
    //last one is bool resize
    mlx.mlx_p = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3d", 1);
    init_player(mlx);
    mlx_loop_hook(mlx.mlx_p, &game_loop, &mlx);
    mlx_key_hook(mlx.mlx_p, &mlx_key, &mlx);
    mlx_loop(mlx.mlx_p);
}

t_map *init_map()
{
    t_map   *map_data;

    //ensures that map_data points to a valid memory location with all its members 
    map_data = ft_calloc(1, sizeof(t_map));
    //i need to calculate how many lines are in the map????
    map_data->map = ft_calloc(6, sizeof(char *)); //!!!!!!!!
    map_data->map[0] = ft_strdup("1111111111111");
    map_data->map[1] = ft_strdup("1000000100001");
    map_data->map[2] = ft_strdup("100P000100001");
    map_data->map[3] = ft_strdup("1000000000001");
    map_data->map[4] = ft_strdup("1111111111111");
    map_data->map[5] = NULL;

    //manually set player position / map with and hight according to the map 
    // cos we dont want to reach "not right"  memory
    map_data->pl_x = 12;
    map_data->pl_y = 2;
    map_data->w_map = 13;
    map_data->h_map = 5;

    return (map_data);
}

int main(int ac, char **av)
{
    if (ac != 1) //!!FIX
        return 1;

    t_map *map_data;

    map_data = init_map();
    start_the_game(map_data);
}
