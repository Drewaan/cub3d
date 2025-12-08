/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 13:37:25 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/12/08 17:23:20 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Inicializa estructura de juego
void	init_game(t_game *game)
{
	ft_bzero(game, sizeof(t_game));

	game->img = NULL;

	game->tex.north = NULL;
	game->tex.south = NULL;
	game->tex.east = NULL;
	game->tex.west = NULL;
	game->tex.floor_color = 0x000000FF;
	game->tex.ceil_color = 0x000000FF;

	game->map.map_array = NULL;
	game->map.width = 0;
	game->map.height = 0;

	ft_bzero(&game->raycast, sizeof(t_raycast));

	ft_bzero(&game->wall_tex, sizeof(t_wall_tex));
}
