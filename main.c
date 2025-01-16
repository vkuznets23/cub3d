#include "cub3d.h"

void	game_loop(void *MLX)
{
	t_mlx	*mlx;

	mlx = MLX;
	mlx_delete_image(mlx->mlx_p, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx_p, SCREEN_WIDTH, SCREEN_HEIGHT);
	hook(mlx, 0, 0);
	cast_rays(mlx);
	mlx_image_to_window(mlx->mlx_p, mlx->img, 0, 0);
}

void	init_player(t_mlx *mlx)
{
	char	c;

	c = mlx->dt->map[mlx->dt->pl_y - 1][mlx->dt->pl_x - 1];
	if (c == 'N')
		mlx->player->angle = 3 * M_PI / 2;
	if (c == 'S')
		mlx->player->angle = M_PI / 2;
	if (c == 'E')
		mlx->player->angle = 0;
	if (c == 'W')
		mlx->player->angle = M_PI;
	mlx->player->player_x = (mlx->dt->pl_x * TILE_SIZE) + TILE_SIZE / 2;
	mlx->player->player_y = (mlx->dt->pl_y * TILE_SIZE) + TILE_SIZE / 2;
	mlx->player->fov = (FOV * M_PI) / 180;
}

int	set_textures(t_mlx *mlx)
{
	mlx->textures->north = mlx_load_png("./textures/11.png");
	if (!mlx->textures->north)
	{
		ft_putstr_fd("Failed to load north texture", 2);
		//free string
		return (1);
	}
	mlx->textures->east = mlx_load_png("./textures/12.png");
	if (!mlx->textures->east)
	{
		ft_putstr_fd("Failed to load east texture", 2);
		return (1);
	}
	mlx->textures->west = mlx_load_png("./textures/13.png");
	if (!mlx->textures->west)
	{
		ft_putstr_fd("Failed to load west texture", 2);
		return (1);
	}
	mlx->textures->south = mlx_load_png("./textures/14.png");
	if (!mlx->textures->south)
	{
		ft_putstr_fd("Failed to load soutn texture", 2);
		return (1);
	}
	return (0);
}

t_data	*init_map(void)
{
	t_data	*dt;

	dt = ft_calloc(1, sizeof(t_data));

	//i need to calculate how many lines are in the map????
	dt->map = ft_calloc(6, sizeof(char *)); //!!!!!!!
	dt->map[0] = ft_strdup("1111111111111");
	dt->map[1] = ft_strdup("1000000100001");
	dt->map[2] = ft_strdup("1000001N00001");
	dt->map[3] = ft_strdup("1000000000001");
	dt->map[4] = ft_strdup("1111111111111");
	dt->map[5] = NULL;

	dt->ff_c[0] = 52;
	dt->ff_c[1] = 21;
	dt->ff_c[2] = 49;

	dt->cc_c[0] = 211;
	dt->cc_c[1] = 211;
	dt->cc_c[2] = 211;


	find_n_position(dt);
	dt->w_map = ft_strlen(dt->map[0]);
	dt->h_map = count_lines(dt->map);
	return (dt);
}

int	main(int ac, char **av)
{
	t_data	*dt;
	t_mlx	mlx;

	if (ac != 1) //!!FIX
		return (1);
	mlx.dt = init_map();
	mlx.player = ft_calloc(1, sizeof(t_player));
	mlx.ray = (t_ray *)ft_calloc(1, sizeof(t_ray));
	mlx.textures = ft_calloc(1, sizeof(t_textures));
	mlx.mlx_p = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3d", 1);
	if (!mlx.mlx_p)	
		ft_exit(&mlx);
	if (set_textures(&mlx) == 1)
		ft_exit(&mlx);
	init_player(&mlx);
	mlx_loop_hook(mlx.mlx_p, &game_loop, &mlx);
	mlx_key_hook(mlx.mlx_p, &mlx_key, &mlx);
	mlx_loop(mlx.mlx_p);
}
