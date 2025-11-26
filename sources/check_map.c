/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:12:55 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/11/24 19:12:59 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	set_direction(t_game *game, char c)
{
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
}

static void	set_camera_plane(t_game *game)
{
	game->player.plane_x = -game->player.dir_y * 0.66;
	game->player.plane_y = game->player.dir_x * 0.66;
}

static void	process_player_tile(t_game *game, char **m, int i, int j)
{
	game->player.pos_x = j + 0.5;
	game->player.pos_y = i + 0.5;
	set_direction(game, m[i][j]);
	set_camera_plane(game);
	m[i][j] = '0';
	game->player_count++;
}

static void	scan_tile(t_game *game, char **m, int i, int j)
{
	char	c;

	c = m[i][j];
	if (ft_strchr("NSEW", c))
		process_player_tile(game, m, i, j);
}

void	locate_player(t_game *game)
{
	int		i;
	int		j;
	char	**m;

	i = 0;
	game->player_count = 0;
	m = game->map.map_array;
	while (i < game->map.map_h)
	{
		j = 0;
		while (j < game->map.map_w)
		{
			scan_tile(game, m, i, j);
			j++;
		}
		i++;
	}
	if (game->player_count != 1)
		error_exit("Invalid player count");
}
