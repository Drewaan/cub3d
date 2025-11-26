/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:19:57 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/11/24 19:21:46 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// texture_loader.c
#include "../includes/cub3d.h"

static mlx_texture_t	*load_png(char *path)
{
	mlx_texture_t	*t;

	t = mlx_load_png(path);
	if (!t)
		error_exit("Failed to load texture");
	return (t);
}

void	load_textures(t_game *game, t_data *d)
{
	game->textures.north = load_png(d->north);
	game->textures.south = load_png(d->south);
	game->textures.west = load_png(d->west);
	game->textures.east = load_png(d->east);
}
