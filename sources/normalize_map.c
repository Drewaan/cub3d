/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:06:16 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/12/10 13:49:34 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	normalize_map(t_map *map)
{
	int		y;
	int		len;
	char	*new;

	y = 0;
	while (y < map->height)
	{
		len = ft_strlen(map->map_array[y]);
		if (len < map->width)
		{
			new = malloc(map->width + 1);
			if (!new)
				return ;

			ft_memset(new, ' ', map->width);
			new[map->width] = '\0';

			ft_memcpy(new, map->map_array[y], len);

			free(map->map_array[y]);
			map->map_array[y] = new;
		}
		y++;
	}
}

static int	is_valid(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ');
}

static void	locate_player(t_parser *p)
{
	for (int i = 0; i < p->map_h; i++)
		for (int j = 0; j < p->map_w; j++)
			if (ft_strchr("NSEW", p->map[i][j]))
			{
				p->player_x = i;
				p->player_y = j;
				p->player_dir = p->map[i][j];
				p->map[i][j] = '0';
			}
	if (p->player_x < 0)
		error_exit("Player missing");
}

static void	flood(char **m, int x, int y, t_parser *p)
{
	if (x < 0 || y < 0 || x >= p->map_h || y >= p->map_w)
		error_exit("Map open");
	if (m[x][y] == '1' || m[x][y] == 'V')
		return ;
	if (m[x][y] == ' ')
		error_exit("Space leak");
	m[x][y] = 'V';
	flood(m, x + 1, y, p);
	flood(m, x - 1, y, p);
	flood(m, x, y + 1, p);
	flood(m, x, y - 1, p);
}

void	check_map_parser(t_parser *p)
{
	char	**copy;

	locate_player(p);
	for (int i = 0; i < p->map_h; i++)
		for (int j = 0; j < p->map_w; j++)
			if (!is_valid(p->map[i][j]))
				error_exit("Invalid map character");
	copy = dup_map(p);
	flood(copy, p->player_x, p->player_y, p);
	free_split(copy);
}
