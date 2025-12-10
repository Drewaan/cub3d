/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_to_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:34:57 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/12/02 15:35:14 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	data_to_game(t_parser *p, t_game *g)
{
	int	i;

	if (!p || !g)
		error_exit("Parser or game not initialized");
	g->map.map_h = p->map_h;
	g->map.map_w = p->map_w;
	g->map.map_array = malloc(sizeof(char *) * (p->map_h + 1));
	if (!g->map.map_array)
		error_exit("Malloc failed in data_to_game");
	for (i = 0; i < p->map_h; i++)
	{
		g->map.map_array[i] = ft_strdup(p->map[i]);
		if (!g->map.map_array[i])
			error_exit("Malloc failed duplicating map row");
	}
	g->map.map_array[i] = NULL;
	g->player.pos_x = p->player_y + 0.5;
	g->player.pos_y = p->player_x + 0.5;
	if (p->player_dir == 'N')
	{
		g->player.dir_x = 0;
		g->player.dir_y = -1;
	}
	if (p->player_dir == 'S')
	{
		g->player.dir_x = 0;
		g->player.dir_y = 1;
	}
	if (p->player_dir == 'W')
	{
		g->player.dir_x = -1;
		g->player.dir_y = 0;
	}
	if (p->player_dir == 'E')
	{
		g->player.dir_x = 1;
		g->player.dir_y = 0;
	}
	if (p->player_dir == 'N')
	{
		g->player.plane_x = 0.66;
		g->player.plane_y = 0;
	}
	if (p->player_dir == 'S')
	{
		g->player.plane_x = -0.66;
		g->player.plane_y = 0;
	}
	if (p->player_dir == 'W')
	{
		g->player.plane_x = 0;
		g->player.plane_y = -0.66;
	}
	if (p->player_dir == 'E')
	{
		g->player.plane_x = 0;
		g->player.plane_y = 0.66;
	}
	g->player.speed = 0.12;
	g->player.rotate_speed = 0.08;
}
