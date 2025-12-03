/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:43:00 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/12/02 15:55:19 by aamaya-g         ###   ########.fr       */
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

int	dim_color(t_color *color, double dist)
{
	int	new_color;

	dist /= 3;
	if (dist < 1)
		dist = 1;
	color -> red /= dist;
	color -> green /= dist;
	color -> blue /= dist;
	new_color = get_rgba(color->red, color->green, color->blue, color->alpha);
	return (new_color);
}

void	draw_stripe(t_game *game, int x, int start, int end)
{
	int		y;
	int		dimmed_color;
	t_color	color;

	y = start;
	get_wall_texture(game);
	set_tex_params(&game -> wall_tex, &game -> raycast);
	while (y <= end)
	{
		game -> wall_tex.tex_y = ((int)game -> wall_tex.tex_pos)
			% game -> wall_tex.tex -> height;
		game -> wall_tex.tex_pos += game -> wall_tex.tex_pos;
		color = get_texture_pixel(game -> wall_tex.tex, game -> wall_tex.tex_x,
				game -> wall_tex.tex_y);
		dimmed_color = dim_color(&color, game -> raycast.wall_dist);
		mlx_put_pixel(game -> img, x, y, dimmed_color);
		y++;
	}
}

void	get_wall_height(t_game *game, int x)
{
	int	line_h;
	int	wall_start;
	int	wall_end;

	line_h = (int)(WIN_H / game -> raycast.wall_dist);
	wall_start = -line_h / 2 + WIN_H / 2;
	if (wall_start < 0)
		wall_start = 0;
	wall_end = line_h / 2 + WIN_H / 2;
	if (wall_end >= WIN_H)
		wall_end = WIN_H - 1;
	game->wall_tex.tex_step = 1.0 * (game->textures.north->height - 1) / line_h;
	game -> wall_tex.tex_pos = (wall_start - WIN_H / 2 + line_h / 2)
		* game -> wall_tex.tex_step;
	draw_stripe(game, x, wall_start, wall_end);
}
