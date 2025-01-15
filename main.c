#include "cub3d.h"

//setting the game
void	game_loop(void *MLX)
{
	t_mlx *mlx;

	mlx = MLX;
	mlx_delete_image(mlx->mlx_p, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx_p, SCREEN_WIDTH, SCREEN_HEIGHT);
	hook(mlx, 0, 0);
	cast_rays(mlx);
	mlx_image_to_window(mlx->mlx_p, mlx->img, 0, 0);
}

void	init_player(t_mlx *mlx)
{
	mlx->player->angle = M_PI;
	mlx->player->player_x = (mlx->dt->pl_x * TILE_SIZE) + TILE_SIZE / 2;
	mlx->player->player_y = (mlx->dt->pl_y * TILE_SIZE) + TILE_SIZE / 2;
	mlx->player->fov = (FOV * M_PI) / 180;

    //I WILL NEED TO CHANGE ANGLE DEPENDING ON THE N W S E
    /*
    The angle of M_PI / 2 (90 degrees) corresponds to the player facing East.
    The angle of M_PI (180 degrees) corresponds to the player facing South.
    The angle of 3 * M_PI / 2 (270 degrees) corresponds to the player facing West.
    An angle of 0 corresponds to the player facing North or 2 * M_PI if you prefer the full circle*/

    // the rest of the variables are initialized to zero by calloc
}

void	start_the_game(t_data *dt)
{
	t_mlx	mlx;

	mlx.dt = dt;
	mlx.player = ft_calloc(1, sizeof(t_player));
	mlx.ray = (t_ray *)ft_calloc(1, sizeof(t_ray));
	mlx.textures = ft_calloc(1, sizeof(t_textures));
	mlx.mlx_p = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3d", 1);

	//TEXTURES
	mlx.textures->north = mlx_load_png("./textures/wall_north.png");
	if (!mlx.textures->north)
	{
        	printf("Failed to load north texture");
        	ft_exit(mlx);
	}
	mlx.textures->east = mlx_load_png("./textures/wall_east.png");
	mlx.textures->west = mlx_load_png("./textures/wall_west.png");
	mlx.textures->south = mlx_load_png("./textures/wall_south.png");

	init_player(&mlx);
	mlx_loop_hook(mlx.mlx_p, &game_loop, &mlx);
	mlx_key_hook(mlx.mlx_p, &mlx_key, &mlx);
	mlx_loop(mlx.mlx_p);
}

t_data	*init()
{
	t_data   *dt;

	dt = ft_calloc(1, sizeof(t_data));

	//i need to calculate how many lines are in the map????
	dt->map = ft_calloc(6, sizeof(char *)); //!!!!!!!
	dt->map[0] = ft_strdup("1111111111111");
	dt->map[1] = ft_strdup("1000000100001");
	dt->map[2] = ft_strdup("100P000100001");
	dt->map[3] = ft_strdup("1000000000001");
	dt->map[4] = ft_strdup("1111111111111");
	dt->map[5] = NULL;

	dt->ff_c[0] = 112;
	dt->ff_c[1] = 128;
	dt->ff_c[2] = 144;

	dt->cc_c[0] = 211;
	dt->cc_c[1] = 211;
	dt->cc_c[2] = 211;


	//manually set player position / map with and hight according to the map 
	// cos we dont want to reach "not right"  memory
	dt->pl_x = 4;
	dt->pl_y = 3;
	dt->w_map = 13;
	dt->h_map = 5;

	return (dt);
}

int	main(int ac, char **av)
{
	if (ac != 1) //!!FIX
		return 1;

	t_data *dt;

	dt = init();
	start_the_game(dt);
}
