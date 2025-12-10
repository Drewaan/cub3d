/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:13:36 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/12/10 13:48:31 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* 1. Inicialización del rayo */
static void	ray_refresh(t_raycast *r, t_player *p, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIN_W - 1;
	r->raydir_x = p->dir_x + p->plane_x * camera_x;
	r->raydir_y = p->dir_y + p->plane_y * camera_x;
	r->map_x = (int)p->pos_x;
	r->map_y = (int)p->pos_y;
	r->delta_dist_x = fabs(1 / r->raydir_x);
	r->delta_dist_y = fabs(1 / r->raydir_y);
	r->hit = 0;
}

/* 2. Determinar step y distancias iniciales */
static void	ray_init_step(t_raycast *r, t_player *p)
{
	if (r->raydir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (p->pos_x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - p->pos_x) * r->delta_dist_x;
	}
	if (r->raydir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (p->pos_y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - p->pos_y) * r->delta_dist_y;
	}
}

/* 3. DDA: avanzar hasta golpear una pared */
static void	ray_dda(t_game *g)
{
	t_raycast	*r;

	r = &g->raycast;
	while (r->hit == 0)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (g->map.map_array[r->map_y][r->map_x] == '1')
			r->hit = 1;
	}
}

/* 4. Calcular distancia perpendicular y wall_x (0..1) */
static void	ray_set_dist_and_wallx(t_game *g)
{
	t_raycast	*r;

	r = &g->raycast;
	if (r->side == 0)
		r->wall_dist = (r->map_x - g->player.pos_x + (1 - r->step_x) / 2)
			/ r->raydir_x;
	else
		r->wall_dist = (r->map_y - g->player.pos_y + (1 - r->step_y) / 2)
			/ r->raydir_y;
	if (r->side == 0)
		r->wall_x = g->player.pos_y + r->wall_dist * r->raydir_y;
	else
		r->wall_x = g->player.pos_x + r->wall_dist * r->raydir_x;
	r->wall_x -= floor(r->wall_x);
	if (r->wall_x < 0.0)
		r->wall_x = 0.0;
	if (r->wall_x > 1.0)
		r->wall_x = 1.0;
}

/* 5. Bucle principal de raycasting */
void	raycast(t_game *game)
{
	int	x;

	x = 0;
	while (x < WIN_W)
	{
		ray_refresh(&game->raycast, &game->player, x);
		ray_init_step(&game->raycast, &game->player);
		ray_dda(game);
		ray_set_dist_and_wallx(game);
		draw_sky_and_floor(game, x);
		get_wall_texture(game);
		get_wall_height(game, x);
		x++;
	}
}
