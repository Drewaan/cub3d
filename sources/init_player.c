/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:04:54 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/12/08 17:24:02 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_player(t_game *game)
{
	if (game->player.pos_x == 0 && game->player.pos_y == 0)
	{
		game->player.pos_x = 2;
		game->player.pos_y = 2;
	}

	game->player.dir_x = -1;
	game->player.dir_y = 0;

	game->player.plane_x = 0;
	game->player.plane_y = 0.66;

	game->player.speed = 0.06;
	game->player.rot_speed = 0.04;
}
