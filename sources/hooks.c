/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 18:22:02 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/12/08 18:07:01 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	key_hook(mlx_key_data_t keydata, void *params)
{
	t_game	*game;

	game = params;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game -> mlx);
}

void    rotate(t_player *p, double angle)
{
    double old_dir_x;
    double old_plane_x;

    old_dir_x = p->dir_x;
    p->dir_x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
    p->dir_y = old_dir_x * sin(angle) + p->dir_y * cos(angle);
    old_plane_x = p->plane_x;
    p->plane_x = p->plane_x * cos(angle) - p->plane_y * sin(angle);
    p->plane_y = old_plane_x * sin(angle) + p->plane_y * cos(angle);
}

void	main_hook(void *params)
{
	t_game	*game;

	game = (t_game *)params;
	raycast(game);
	if (mlx_is_key_down(game -> mlx, MLX_KEY_A))
		move_left(game);
	if (mlx_is_key_down(game -> mlx, MLX_KEY_D))
		move_right(game);
	if (mlx_is_key_down(game -> mlx, MLX_KEY_W))
		move_forward(game);
	if (mlx_is_key_down(game -> mlx, MLX_KEY_S))
		move_backward(game);
	if (mlx_is_key_down(game -> mlx, MLX_KEY_LEFT))
		rotate(&game -> player, -game -> player.rot_speed);
	if (mlx_is_key_down(game -> mlx, MLX_KEY_RIGHT))
		rotate(&game -> player, game -> player.rot_speed);
}
