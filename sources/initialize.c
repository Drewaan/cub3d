/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:40:10 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/11/24 19:46:09 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	data_init(t_data *data)
{
	data -> north = NULL;
	data -> south = NULL;
	data -> west = NULL;
	data -> east = NULL;
	data -> floor.red = -1;
	data -> floor.green = -1;
	data -> floor.blue = -1;
	data -> ceiling.red = -1;
	data -> ceiling.green = -1;
	data -> ceiling.blue = -1;
	data -> map_start = 0;
	data -> map_lines = 0;
}

void	set_plane(t_player *player, char dir)
{
	if (dir == 'N')
	{
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (dir == 'S')
	{
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else if (dir == 'W')
	{
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
	else if (dir == 'E')
	{
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
}

void	set_dir(t_player *player, char dir)
{
	if (dir == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
	}
	else if (dir == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}
	else if (dir == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
	else if (dir == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}
	set_plane(player, dir);
}
