/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhirvone <jhirvone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:52:07 by jhirvone          #+#    #+#             */
/*   Updated: 2025/01/20 12:52:08 by jhirvone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_strdup_trim(t_parsing *pars, char *s)
{
	int		start;
	int		end;
	int		len;
	char	*result;

	start = 0;
	while (s[start] && s[start] == ' ')
		start++;
	if (!s[start])
		parse_clean_exit(pars, 1, "Error\nTexture cannot be empty\n");
	end = ft_strlen(s) - 1;
	while (end >= start && s[end] == ' ')
		end--;
	if (end < start)
		parse_clean_exit(pars, 1, "Error\nTexture cannot be empty\n");
	len = end - start + 1;
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	len = 0;
	while (start <= end)
		result[len++] = s[start++];
	result[len] = 0;
	return (result);
}

int	count_rows(char **map)
{
	int	rows;

	rows = 0;
	while (map[rows])
		rows++;
	return (rows);
}

int	find_longest(char **map)
{
	int	i;
	int	longest;
	int	current;

	i = 0;
	longest = 0;
	current = 0;
	while (map[i])
	{
		current = ft_strlen(map[i]);
		if (current > longest)
			longest = current;
		i++;
	}
	return (longest);
}

void	fill_map(t_parsing *pars)
{
	int	i;
	int	j;

	i = 0;
	while (pars->norm_map[i])
	{
		j = 0;
		while (pars->norm_map[i][j])
		{
			if (pars->norm_map[i][j] == ' ')
				pars->norm_map[i][j] = '1';
			if (pars->norm_map[i][j] == '.')
				pars->norm_map[i][j] = '0';
			j++;
		}
		i++;
	}
}

bool	flood_fill(char **map, int x, int y, int rows)
{
	int	col;

	if (x >= 0 && map[x])
		col = ft_strlen(map[x]);
	else
		return (false);
	if (x < 0 || x >= rows || y < 0 || y >= col || map[x][y] == ' ')
		return (false);
	if (map[x][y] == '.' || map[x][y] == '1')
		return (true);
	if (map[x][y] == '0')
		map[x][y] = '.';
	return (flood_fill(map, x + 1, y, rows)
		&& flood_fill(map, x - 1, y, rows)
		&& flood_fill(map, x, y + 1, rows)
		&& flood_fill(map, x, y - 1, rows));
}
