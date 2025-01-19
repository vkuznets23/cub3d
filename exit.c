#include "cub3d.h"

void	free_textures_string(t_parsing *pars)
{
	if (pars->north)
	{
		free(pars->north);
		pars->north = NULL;
	}
	if (pars->south)
	{
		free(pars->south);
		pars->south = NULL;
	}
	if (pars->west)
	{
		free(pars->west);
		pars->west = NULL;
	}
	if (pars->east)
	{
		free(pars->east);
		pars->east = NULL;
	}
}

static void	ft_delete_textures(t_textures *textures)
{
	if (textures->north)
		mlx_delete_texture(textures->north);
	if (textures->south)
		mlx_delete_texture(textures->south);
	if (textures->west)
		mlx_delete_texture(textures->west);
	if (textures->east)
		mlx_delete_texture(textures->east);
}

void	ft_exit(t_mlx *mlx)
{
	mlx_delete_image(mlx->mlx_p, mlx->img);
	mlx_close_window(mlx->mlx_p);
	ft_delete_textures(mlx->textures);
	free(mlx->textures);
	free(mlx->player);
	free(mlx->ray);
	free_array(&mlx->dt->map);
	free(mlx->dt);
	mlx_terminate(mlx->mlx_p);
	ft_putstr_fd("Game closed\n", 1);
	exit(0);
}
