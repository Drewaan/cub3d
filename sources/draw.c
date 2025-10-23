/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:43:00 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/10/21 19:16:08 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_sky_and_floor(t_game *game, int x)
{
	int	y;

	y = 0;
	while (y < WIN_H / 2)
	{
		mlx_put_pixel(game -> img, x, y, game -> textures.ceiling_color);
		y++;
	}
	while (y < WIN_H)
	{
		mlx_put_pixel(game -> img, x, y, game -> textures.floor_color);
		y++;
	}
}

