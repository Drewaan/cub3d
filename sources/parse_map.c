/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 13:55:54 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/12/08 17:37:53 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	find_map_start(char **lines, int i)
{
	while (lines[i])
	{
		if (ft_strchr(lines[i], '1') || ft_strchr(lines[i], '0'))
			return (i);
		i++;
	}
	return (-1);
}

static void	calc_map_size(t_map *map, char **lines, int start)
{
	int	i;
	int	len;

	i = start;
	map->height = 0;
	map->width = 0;
	while (lines[i] && lines[i][0] != '\0')
	{
		len = ft_strlen(lines[i]);
		if (len > map->width)
			map->width = len;
		map->height++;
		i++;
	}
}

static int	copy_map(t_map *map, char **lines, int start)
{
	int	i;
	int	row;

	map->map_array = malloc(sizeof(char *) * (map->height + 1));
	if (!map->map_array)
		return (1);

	row = 0;
	i = start;
	while (row < map->height)
	{
		map->map_array[row] = ft_strdup(lines[i]);
		if (!map->map_array[row])
			return (1);
		row++;
		i++;
	}
	map->map_array[row] = NULL;
	return (0);
}

static int	set_player_pos(t_game *game, char c, int y, int x)
{
	if (game->player.pos_x != 0 || game->player.pos_y != 0)
		return (1);

	game->player.pos_x = x + 0.5;
	game->player.pos_y = y + 0.5;

	if (c == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
	}
	else if (c == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
	}
	else if (c == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
	}
	else if (c == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
	}
	return (0);
}

static int	parse_player(t_game *game)
{
	int	y;
	int	x;
	char	c;

	y = 0;
	while (game->map.map_array[y])
	{
		x = 0;
		while (game->map.map_array[y][x])
		{
			c = game->map.map_array[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (set_player_pos(game, c, y, x))
					return (1);
				game->map.map_array[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	return (game->player.pos_x == 0 ? 1 : 0);
}

int	parse_map(t_game *game, char **lines, int *i)
{
	int	start;

	start = find_map_start(lines, *i);
	if (start < 0)
		return (1);

	calc_map_size(&game->map, lines, start);

	if (copy_map(&game->map, lines, start))
		return (1);

	if (parse_player(game))
		return (1);

	normalize_map(&game->map);
	return (0);
}
