/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 13:55:54 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/12/08 22:15:38 by vlorenzo         ###   ########.fr       */
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

/* ---------------- CALCULATE MAP SIZE ---------------- */

static void	calc_map_size(t_map *map, char **lines, int start)
{
	int		i;
	int		len;

	map->height = 0;
	map->width = 0;
	i = start;

	while (lines[i] && ft_strlen(lines[i]) > 0)
	{
		len = ft_strlen(lines[i]);
		if (len > map->width)
			map->width = len;
		map->height++;
		i++;
	}
}

/* ---------------- COPY MAP RECTANGULAR ---------------- */

static int	copy_map(t_map *map, char **lines, int start)
{
	int	row;
	int	i;
	int	len;

	map->map_array = malloc(sizeof(char *) * (map->height + 1));
	if (!map->map_array)
		return (1);

	row = 0;
	i = start;
	while (row < map->height)
	{
		map->map_array[row] = malloc(map->width + 1);
		if (!map->map_array[row])
			return (1);

		len = ft_strlen(lines[i]);
		ft_memset(map->map_array[row], ' ', map->width);
		ft_memcpy(map->map_array[row], lines[i], len);
		map->map_array[row][map->width] = '\0';

		row++;
		i++;
	}
	map->map_array[row] = NULL;
	return (0);
}

/* ---------------- PLAYER POSITION ---------------- */

static int	set_player_pos(t_game *g, char c, int y, int x)
{
	if (g->player.has_spawn)
		return (1);

	g->player.pos_x = x + 0.5;
	g->player.pos_y = y + 0.5;
	g->player.has_spawn = 1;

	if (c == 'N')
		(g->player.dir_x = 0, g->player.dir_y = -1);
	else if (c == 'S')
		(g->player.dir_x = 0, g->player.dir_y = 1);
	else if (c == 'E')
		(g->player.dir_x = 1, g->player.dir_y = 0);
	else if (c == 'W')
		(g->player.dir_x = -1, g->player.dir_y = 0);

	return (0);
}

static int	parse_player(t_game *g)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (g->map.map_array[y])
	{
		x = 0;
		while (g->map.map_array[y][x])
		{
			c = g->map.map_array[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (set_player_pos(g, c, y, x))
					return (1);
				g->map.map_array[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	return (g->player.has_spawn == 0);
}

/* ---------------- MAIN ENTRY ---------------- */

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
