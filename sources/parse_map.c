/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 13:55:54 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/12/08 22:38:14 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub3d.h"

static int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' ||
			c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	find_map_start(char **lines, int i)
{
	while (lines[i])
	{
		int j = 0;
		while (lines[i][j])
		{
			if (is_valid_map_char(lines[i][j]))
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

static int	calc_map_size(t_map *map, char **lines, int start)
{
	int i = start;
	int len;

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
	return (0);
}

int set_player_pos(t_game *g, char c, int y, int x)
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

static int	copy_and_validate(t_game *g, char **lines, int start)
{
	int y = 0, x, len;
	char c;

	g->map.map_array = malloc(sizeof(char *) * (g->map.height + 1));
	if (!g->map.map_array)
		return (1);

	while (y < g->map.height)
	{
		g->map.map_array[y] = malloc(g->map.width + 1);
		if (!g->map.map_array[y])
			return (1);

		ft_memset(g->map.map_array[y], ' ', g->map.width);
		g->map.map_array[y][g->map.width] = '\0';

		len = ft_strlen(lines[start + y]);
		ft_memcpy(g->map.map_array[y], lines[start + y], len);
		
		x = 0;
		while (x < len)
		{
			c = g->map.map_array[y][x];
			if (!is_valid_map_char(c))
				return (ft_printf("Error: carácter inválido '%c'\n", c), 1);

			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (g->player.has_spawn)
					return (ft_printf("Error: múltiples jugadores\n"), 1);
				set_player_pos(g, c, y, x);
				g->map.map_array[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	g->map.map_array[y] = NULL;
	return (g->player.has_spawn == 0);
}

int	parse_map(t_game *game, char **lines, int *i)
{
	int start;

	start = find_map_start(lines, *i);
	if (start < 0)
		return (ft_printf("Error: no se encontró mapa\n"), 1);

	calc_map_size(&game->map, lines, start);

	if (calc_map_size(&game->map, lines, start))
		return (1);

	if (copy_and_validate(game, lines, start))
		return (1);

	return (0);
}