/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuznets <vkuznets@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:58:39 by vkuznets          #+#    #+#             */
/*   Updated: 2025/01/20 12:04:45 by vkuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * This function is used to combine individual red, green, blue, and alpha
 * (transparency) values into a single 32-bit integer
 *
 * alpha is used to represent the transparency or opacity of the color.
*/
int	get_rgb(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a << 0);
}

/**
 * This function is used to reverse the byte order (also called endianness
 * swapping) of a 32-bit integer. It takes a 4-byte integer c and rearranges
 * the bytes so that the most significant byte becomes the least significant
 * byte and vice versa
 *
 * significant byte is the byte that holds the most important part of a number
 * or value when it's split into multiple bytes
 *
 * (!) colors might be stored in a different byte order
*/
int	reverse_bytes(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}

/**
 * Custome function to check if the pixel coordinates (x and y) are within
 * the screen boundaries before drawing the pixel.
 *
 * @mlx struct that holds all neccessary data
 * @x and y coordinated
 * @color color that we pass to render
*/
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	if (x < 0)
		return ;
	else if (x >= SCREEN_WIDTH)
		return ;
	if (y < 0)
		return ;
	else if (y >= SCREEN_HEIGHT)
		return ;
	mlx_put_pixel(mlx->img, x, y, color);
}

/**
 * Function is used to count lines int he map
*/
int	count_lines(char **map)
{
	int	count;

	count = 0;
	while (map[count] != NULL)
		count++;
	return (count);
}

/**
 * Function is used to find player position on the map
*/
void	find_n_position(t_data *dt)
{
	int	y;
	int	x;

	y = 0;
	while (dt->map[y] != NULL)
	{
		x = 0;
		while (dt->map[y][x] != '\0')
		{
			if (dt->map[y][x] == 'N' || dt->map[y][x] == 'S'
				|| dt->map[y][x] == 'W' || dt->map[y][x] == 'E')
			{
				dt->pl_x = x;
				dt->pl_y = y;
			}
			x++;
		}
		y++;
	}
}
