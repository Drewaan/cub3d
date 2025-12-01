/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:23:32 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/12/01 22:52:36 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/parser.h"
#include <math.h>

/* ------------------------------------------------------------ */
/*  REFRESH RAY (camera space + ray direction + deltas)         */
/* ------------------------------------------------------------ */
void	ray_refresh(t_ray *ray, t_player *player, int x)
{
	ray->hit = 0;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->camera = 2.0 * x / (double)WIN_W - 1.0;
	ray->ray_x = player->dir_x + player->plane_x * ray->camera;
	ray->ray_y = player->dir_y + player->plane_y * ray->camera;
	ray->delta_dist_x = (ray->ray_x == 0.0) ? 1e30 : fabs(1 / ray->ray_x);
	ray->delta_dist_y = (ray->ray_y == 0.0) ? 1e30 : fabs(1 / ray->ray_y);
}

/* ------------------------------------------------------------ */
/*  STEP & INITIAL SIDE DISTANCES                               */
/* ------------------------------------------------------------ */
void	ray_dir(t_ray *ray, t_player *player)
{
	if (ray->ray_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y)
			* ray->delta_dist_y;
	}
}

/* ------------------------------------------------------------ */
/*  DDA LOOP                                                    */
/* ------------------------------------------------------------ */
void	check_hit(t_game *game)
{
	int	max_y;
	int	max_x;

	max_y = game->map.map_h;
	max_x = game->map.map_w;
	while (game->raycast.hit == 0)
	{
		if (game->raycast.side_dist_x < game->raycast.side_dist_y)
		{
			game->raycast.side_dist_x += game->raycast.delta_dist_x;
			game->raycast.map_x += game->raycast.step_x;
			game->raycast.side_hit = 0;
		}
		else
		{
			game->raycast.side_dist_y += game->raycast.delta_dist_y;
			game->raycast.map_y += game->raycast.step_y;
			game->raycast.side_hit = 1;
		}
		/* Bounds check avoiding segfault */
		if (game->raycast.map_x < 0 || game->raycast.map_x >= max_x
			|| game->raycast.map_y < 0 || game->raycast.map_y >= max_y)
		{
			game->raycast.hit = 1;
			break ;
		}
		if (game->map.map_array[game->raycast.map_y][game->raycast.map_x] == '1')
			game->raycast.hit = 1;
	}
}

/* ------------------------------------------------------------ */
/*  DISTANCE CALCULATION                                        */
/* ------------------------------------------------------------ */
void	set_dist(t_game *game)
{
	if (game->raycast.side_hit == 0)
		game->raycast.wall_dist = game->raycast.side_dist_x
			- game->raycast.delta_dist_x;
	else
		game->raycast.wall_dist = game->raycast.side_dist_y
			- game->raycast.delta_dist_y;
	if (game->raycast.wall_dist <= 0.000001)
		game->raycast.wall_dist = 0.000001;
	if (game->raycast.side_hit == 0)
		game->raycast.wall_x = game->player.pos_y + game->raycast.wall_dist
			* game->raycast.ray_y;
	else
		game->raycast.wall_x = game->player.pos_x + game->raycast.wall_dist
			* game->raycast.ray_x;
	game->raycast.wall_x -= floor(game->raycast.wall_x);
}

/* ------------------------------------------------------------ */
/*  MAIN RAYCAST LOOP                                           */
/* ------------------------------------------------------------ */
void	raycast(t_game *game)
{
	int	x;

	for (x = 0; x < WIN_W; x++)
	{
		ray_refresh(&game->raycast, &game->player, x);
		ray_dir(&game->raycast, &game->player);
		check_hit(game);
		set_dist(game);
		draw_sky_and_floor(game, x);
		get_wall_height(game, x);
	}
}
