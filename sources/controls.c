/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 17:51:54 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/12/08 18:06:49 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_forward(t_game *game)
{
	double	newposx;
	double	newposy;
	double	collision_margin;

	collision_margin = 0.2;
	newposx = game -> player.pos_x + game -> player.dir_x * game->player.speed;
	newposy = game -> player.pos_y + game -> player.dir_y * game->player.speed;
	if (game -> map.map_array[(int)game -> player.pos_y][(int)(newposx
		+ game -> player.dir_x * collision_margin)] != '1')
		game -> player.pos_x = newposx;
	if (game -> map.map_array[(int)(newposy + game -> player.dir_y
			* collision_margin)][(int)game -> player.pos_x] != '1')
		game -> player.pos_y = newposy;
}

void	move_backward(t_game *game)
{
	double	newposx;
	double	newposy;
	double	collision_margin;

	collision_margin = 0.2;
	newposx = game -> player.pos_x - game -> player.dir_x * game->player.speed;
	newposy = game -> player.pos_y - game -> player.dir_y * game->player.speed;
	if (game -> map.map_array[(int)game -> player.pos_y][(int)(newposx
		- game -> player.dir_x * collision_margin)] != '1')
		game -> player.pos_x = newposx;
	if (game -> map.map_array[(int)(newposy - game -> player.dir_y
			* collision_margin)][(int)game -> player.pos_x] != '1')
		game -> player.pos_y = newposy;
}

void	move_right(t_game *game)
{
	double	newposx;
	double	newposy;
	double	collision_margin;

	collision_margin = 0.2;
	newposx = game -> player.pos_x - game -> player.dir_y * game->player.speed;
	newposy = game -> player.pos_y + game -> player.dir_x * game->player.speed;
	if (game -> map.map_array[(int)game -> player.pos_y][(int)(newposx
		- game -> player.dir_y * collision_margin)] != '1')
		game -> player.pos_x = newposx;
	if (game -> map.map_array[(int)(newposy + game -> player.dir_x
			* collision_margin)][(int)game -> player.pos_x] != '1')
		game -> player.pos_y = newposy;
}

void	move_left(t_game *game)
{
	double	newposx;
	double	newposy;
	double	collision_margin;

	collision_margin = 0.2;
	newposx = game -> player.pos_x + game -> player.dir_y * game->player.speed;
	newposy = game -> player.pos_y - game -> player.dir_x * game->player.speed;
	if (game -> map.map_array[(int)game -> player.pos_y][(int)(newposx
		+ game -> player.dir_y * collision_margin)] != '1')
		game -> player.pos_x = newposx;
	if (game -> map.map_array[(int)(newposy - game -> player.dir_x
			* collision_margin)][(int)game -> player.pos_x] != '1')
		game -> player.pos_y = newposy;
}
