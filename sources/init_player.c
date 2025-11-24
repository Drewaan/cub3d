/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:14:30 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/11/24 19:14:35 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// init_player.c
#include "cub3d.h"

void	init_player(t_data *d)
{
	if (d->player_dir == 'N')
	{
		d->dir_x = 0;
		d->dir_y = -1;
		d->plane_x = 0.66;
		d->plane_y = 0;
	}
	if (d->player_dir == 'S')
	{
		d->dir_x = 0;
		d->dir_y = 1;
		d->plane_x = -0.66;
		d->plane_y = 0;
	}
	if (d->player_dir == 'E')
	{
		d->dir_x = 1;
		d->dir_y = 0;
		d->plane_x = 0;
		d->plane_y = 0.66;
	}
	if (d->player_dir == 'W')
	{
		d->dir_x = -1;
		d->dir_y = 0;
		d->plane_x = 0;
		d->plane_y = -0.66;
	}
}