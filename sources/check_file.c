/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:10:48 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/11/26 13:52:52 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_file_extension(char *p)
{
	int	len;

	len = ft_strlen(p);
	if (len < 4 || ft_strncmp(p + len - 4, ".cub", 4) != 0)
		error_exit("Invalid file extension");
}

static void	check_color_range(t_color c)
{
	if (c.red < 0 || c.red > 255 || \
		c.green < 0 || c.green > 255 || \
		c.blue < 0 || c.blue > 255)
		error_exit("Color out of range");
}

void	check_identifiers(t_data *d)
{
	if (!d->north || !d->south || !d->west || !d->east)
		error_exit("Missing texture path");
	if (d->floor.red == -1 || d->floor.green == -1 || d->floor.blue == -1)
		error_exit("Missing floor color");
	if (d->ceiling.red == -1 || d->ceiling.green == -1 || d->ceiling.blue == -1)
		error_exit("Missing ceiling color");
	check_color_range(d->floor);
	check_color_range(d->ceiling);
}

static void	flood(char **m, int x, int y, t_game *game)
{
	if (x < 0 || y < 0 || x >= game->map.map_h || y >= game->map.map_w)
		error_exit("Map not closed");
	if (m[x][y] == '1' || m[x][y] == 'V')
		return ;
	if (m[x][y] == ' ')
		error_exit("Space leak");
	m[x][y] = 'V';
	flood(m, x + 1, y, game);
	flood(m, x - 1, y, game);
	flood(m, x, y + 1, game);
	flood(m, x, y - 1, game);
}

void	check_map(t_game *game)
{
	int		i;
	int		j;
	char	c;
	char	**copy;

	locate_player(game);
	i = 0;
	while (i < game->map.map_h)
	{
		j = 0;
		while (j < game->map.map_w)
		{
			c = game->map.map_array[i][j];
			if (!valid_char(c) && c != ' ')
				error_exit("Invalid map character");
			j++;
		}
		i++;
	}
	copy = dup_map(&game->map);
	flood(copy, (int)game->player.pos_y, (int)game->player.pos_x, game);
	free_map(copy);
}
