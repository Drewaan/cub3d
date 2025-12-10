/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 19:39:30 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/12/10 17:59:36 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_wall_height(t_game *game, int x)
{
	int	line_h;
	int	wall_start;
	int	wall_end;

	line_h = (int)(WIN_H / game->raycast.wall_dist);
	wall_start = -line_h / 2 + WIN_H / 2;
	if (wall_start < 0)
		wall_start = 0;
	wall_end = line_h / 2 + WIN_H / 2;
	if (wall_end >= WIN_H)
		wall_end = WIN_H - 1;
	game->wall_tex.tex_step = 1.0 * (game->textures.north->height - 1) / line_h;
	game->wall_tex.tex_pos = (wall_start - WIN_H / 2 + line_h / 2)
		* game->wall_tex.tex_step;
	draw_stripe(game, x, wall_start, wall_end);
}

int	is_valid(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ');
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W');
}
