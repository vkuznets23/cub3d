/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuznets <vkuznets@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:15:41 by vkuznets          #+#    #+#             */
/*   Updated: 2025/01/20 13:55:29 by vkuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

static int	load_texture(char *path, mlx_texture_t **textur, char *name)
{
	*textur = mlx_load_png(path);
	if (!*textur)
	{
		ft_putstr_fd("Error\nFailed to load ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(" texture\n", 2);
		return (1);
	}
	return (0);
}

int	set_textures(t_mlx *mlx, t_parsing *pars)
{
	if (load_texture(pars->north, &mlx->textures->north, "north"))
		return (1);
	if (load_texture(pars->east, &mlx->textures->east, "east"))
		return (1);
	if (load_texture(pars->west, &mlx->textures->west, "west"))
		return (1);
	if (load_texture(pars->south, &mlx->textures->south, "south"))
		return (1);
	free_textures_string(pars);
	return (0);
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
