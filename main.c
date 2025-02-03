/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuznets <vkuznets@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:12:59 by vkuznets          #+#    #+#             */
/*   Updated: 2025/01/20 14:27:02 by jhirvone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	init_mlx_resources(t_mlx *mlx)
{
	mlx->mlx_p = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3d", 0);
	if (!mlx->mlx_p)
	{
		ft_putstr_fd("Error\nMLX initialization failed\n", 2);
		return (1);
	}
	mlx->player = ft_calloc(1, sizeof(t_player));
	mlx->ray = (t_ray *)ft_calloc(1, sizeof(t_ray));
	mlx->textures = ft_calloc(1, sizeof(t_textures));
	if (!mlx->player || !mlx->ray || !mlx->textures)
	{
		ft_putstr_fd("Error\nMemory allocation failed\n", 2);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_mlx		mlx;
	t_parsing	pars;

	if (ac != 2)
	{
		ft_putstr_fd("Error\nUsage: ./cub3d <example.cub>\n", 2);
		return (1);
	}
	init_pars_struct(&pars, av[1]);
	parse_file(&pars);
	mlx.dt = init_map(&pars);
	if (init_mlx_resources(&mlx) == 1)
		ft_exit(&mlx);
	if (set_textures(&mlx, &pars) == 1)
		ft_exit(&mlx);
	init_player(&mlx);
	mlx_loop_hook(mlx.mlx_p, &game_loop, &mlx);
	mlx_key_hook(mlx.mlx_p, &mlx_key, &mlx);
	mlx_loop(mlx.mlx_p);
	ft_exit(&mlx);
}
