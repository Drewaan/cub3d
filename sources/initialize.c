/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:40:10 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/12/02 15:43:01 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* void	data_init(t_data *data)
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
} */

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
void	parser_init(t_parser *p)
{
	p->paths.no = NULL;
	p->paths.so = NULL;
	p->paths.we = NULL;
	p->paths.ea = NULL;
	p->floor_color.red = -1;
	p->floor_color.green = -1;
	p->floor_color.blue = -1;
	p->floor_color.alpha = 255;
	p->ceil_color = p->floor_color;
	p->map = NULL;
	p->map_h = 0;
	p->map_w = 0;
	p->player_x = -1;
	p->player_y = -1;
	p->player_dir = 0;
	p->dir_x = 0;
	p->dir_y = 0;
	p->plane_x = 0;
	p->plane_y = 0;
}
