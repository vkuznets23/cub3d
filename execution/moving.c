/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuznets <vkuznets@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:49:53 by vkuznets          #+#    #+#             */
/*   Updated: 2025/01/20 12:04:03 by vkuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * This function ensures that the player's state (e.g., movement direction 
 * or rotation) is updated appropriately when the associated key is
 * no longer pressed.
 *
 * @keydata The key event data, including the key and its action.
 * @mlx The main game structure containing player and map data.
 */
static void	ft_release(mlx_key_data_t keydata, t_mlx *mlx)
{
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
		mlx->player->left_right = 0;
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
		mlx->player->left_right = 0;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
		mlx->player->up_down = 0;
	else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
		mlx->player->up_down = 0;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		mlx->player->rotation = 0;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		mlx->player->rotation = 0;
}

/**
 * This function maps key presses to corresponding movement or rotation flags,
 * enabling the player to move or rotate in response to user input. It also
 * handles the escape key for exiting the game.
 *
 * @keydata The key event data, including the key and its action.
 * @ml A void pointer to the main game structure (cast to t_mlx internally).
 */
void	mlx_key(mlx_key_data_t keydata, void *ml)
{
	t_mlx	*mlx;

	mlx = ml;
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		ft_exit(mlx);
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS))
		mlx->player->left_right = -1;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS))
		mlx->player->left_right = 1;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS))
		mlx->player->up_down = -1;
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		mlx->player->up_down = 1;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		mlx->player->rotation = -1;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		mlx->player->rotation = 1;
	ft_release(keydata, mlx);
}

/**
 * This function updates the player's position while performing collision
 * detection against walls in the map. Movement is allowed only if 
 * the target position is not inside a wall.
 *
 * @mlx The main game structure containing player and map data.
 * @move_x The horizontal movement amount.
 * @move_y The vertical movement amount.
 */
static void	move_player(t_mlx *mlx, int move_x, int move_y)
{
	int	new_x;
	int	new_y;
	int	map_grid_x;
	int	map_grid_y;

	new_x = roundf(mlx->player->player_x + move_x);
	new_y = roundf(mlx->player->player_y + move_y);
	map_grid_x = (new_x / TILE_SIZE);
	map_grid_y = (new_y / TILE_SIZE);
	if (mlx->dt->map[map_grid_y][map_grid_x] != '1'
		&& (mlx->dt->map[map_grid_y][mlx->player->player_x / TILE_SIZE] != '1'
		&& mlx->dt->map[mlx->player->player_y / TILE_SIZE][map_grid_x] != '1'))
	{
		mlx->player->player_x = new_x;
		mlx->player->player_y = new_y;
	}
}

/**
 * This function adjusts the player's angle based on the direction of rotation.
 * It ensures the angle stays within the range [0, 2π].
 *
 * @mlx The main game structure containing player data.
 * @i The rotation direction: 1 for clockwise, 0 for counterclockwise.
 */
static void	rotate_player(t_mlx *mlx, int i)
{
	if (i == 1)
	{
		mlx->player->angle += ROTATION_SPEED;
		if (mlx->player->angle > 2 * M_PI)
			mlx->player->angle -= 2 * M_PI;
	}
	else
	{
		mlx->player->angle -= ROTATION_SPEED;
		if (mlx->player->angle < 0)
			mlx->player->angle += 2 * M_PI;
	}
}

/**
 * This function processes the player's movement and rotation in all directions
 * by interpreting the `left_right`, `up_down`, and `rotation` flags.
 * It calculates movement vectors and delegates the actual movement
 * to `move_player`.
 *
 * @mlx The main game structure containing player and map data.
 * @move_x Placeholder for horizontal movement (calculated internally).
 * @move_y Placeholder for vertical movement (calculated internally).
 */
void	hook(t_mlx *mlx, int move_x, int move_y)
{
	if (mlx->player->rotation == 1)
		rotate_player(mlx, 1);
	if (mlx->player->rotation == -1)
		rotate_player(mlx, 0);
	if (mlx->player->left_right == 1)
	{
		move_x = -sin(mlx->player->angle) * PLAYER_SPEED;
		move_y = cos(mlx->player->angle) * PLAYER_SPEED;
	}
	if (mlx->player->left_right == -1)
	{
		move_x = sin(mlx->player->angle) * PLAYER_SPEED;
		move_y = -cos(mlx->player->angle) * PLAYER_SPEED;
	}
	if (mlx->player->up_down == 1)
	{
		move_y = sin(mlx->player->angle) * PLAYER_SPEED;
		move_x = cos(mlx->player->angle) * PLAYER_SPEED;
	}
	if (mlx->player->up_down == -1)
	{
		move_y = -sin(mlx->player->angle) * PLAYER_SPEED;
		move_x = -cos(mlx->player->angle) * PLAYER_SPEED;
	}
	move_player(mlx, move_x, move_y);
}
