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

	c = mlx->dt->map[mlx->dt->pl_y][mlx->dt->pl_x];
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

int	set_textures(t_mlx *mlx, t_parsing *pars)
{
	mlx->textures->north = mlx_load_png(pars->north);
	if (!mlx->textures->north)
	{
		ft_putstr_fd("Error\nFailed to load north texture\n", 2);
		free_textures_string(pars);
		return (1);
	}
	mlx->textures->east = mlx_load_png(pars->east);
	if (!mlx->textures->east)
	{
		ft_putstr_fd("Error\nFailed to load east texture\n", 2);
		free_textures_string(pars);
		return (1);
	}
	mlx->textures->west = mlx_load_png(pars->west);
	if (!mlx->textures->west)
	{
		ft_putstr_fd("Error\nFailed to load west texture\n", 2);
		free_textures_string(pars);
		return (1);
	}
	mlx->textures->south = mlx_load_png(pars->south);
	if (!mlx->textures->south)
	{
		ft_putstr_fd("Error\nFailed to load soutn texture\n", 2);
		free_textures_string(pars);
		return (1);
	}
	free_textures_string(pars);
	return (0);
}

///
void	parse_file(t_parsing *pars)
{
	validate_file(pars);
	gather_data(pars, pars->map);
	validate_map(pars, pars->map + pars->map_start);
}

void	init_pars_struct(t_parsing *pars, char *file)
{
	pars->file = file;
	pars->cont = NULL;
	pars->north = NULL;
	pars->south = NULL;
	pars->east = NULL;
	pars->west = NULL;
	pars->map = NULL;
	pars->norm_map = NULL;
	pars->fd = -1;
	pars->floor[0] = -1;
	pars->floor[1] = -1;
	pars->floor[2] = -1;
	pars->ceiling[0] = -1;
	pars->ceiling[1] = -1;
	pars->ceiling[2] = -1;
	pars->map_start = -1;
}
///

t_data	*init_map(t_parsing *pars)
{
	t_data	*dt;

	dt = ft_calloc(1, sizeof(t_data));
	dt->map = pars->norm_map;
	dt->ff_c[0] = pars->floor[0];
	dt->ff_c[1] = pars->floor[1];
	dt->ff_c[2] = pars->floor[2];
	dt->cc_c[0] = pars->ceiling[0];
	dt->cc_c[1] = pars->ceiling[1];
	dt->cc_c[2] = pars->ceiling[2];
	find_n_position(dt);
	dt->w_map = ft_strlen(dt->map[0]);
	dt->h_map = count_lines(dt->map);
	return (dt);
}

int	main(int ac, char **av)
{
	t_data	*dt;
	t_mlx	mlx;
	t_parsing	pars;

	
	if (ac != 2)
	{
		ft_putstr_fd("Error\nUsage: ./cub3d <example.cub>\n", 2);
		return (1);
	}
	init_pars_struct(&pars, av[1]);
	parse_file(&pars);
	mlx.dt = init_map(&pars);
	mlx.player = ft_calloc(1, sizeof(t_player));
	mlx.ray = (t_ray *)ft_calloc(1, sizeof(t_ray));
	mlx.textures = ft_calloc(1, sizeof(t_textures));
	mlx.mlx_p = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3d", 0);
	if (!mlx.mlx_p)
	{
		ft_putstr_fd("Error\n MLX initialization failed\n", 2);
		ft_exit(&mlx);
	}
	if (set_textures(&mlx, &pars) == 1)
		ft_exit(&mlx);
	init_player(&mlx);
	mlx_loop_hook(mlx.mlx_p, &game_loop, &mlx);
	mlx_key_hook(mlx.mlx_p, &mlx_key, &mlx);
	mlx_loop(mlx.mlx_p);
	ft_exit(&mlx);
}
