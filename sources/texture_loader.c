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
#include "cub3d.h"

static mlx_texture_t	*load_png(char *path)
{
	mlx_texture_t	*t;

	t = mlx_load_png(path);
	if (!t)
		error_exit("Texture load failed");
	return (t);
}

void	load_textures(t_data *d)
{
	d->tex[NO] = load_png(d->paths.no);
	d->tex[SO] = load_png(d->paths.so);
	d->tex[WE] = load_png(d->paths.we);
	d->tex[EA] = load_png(d->paths.ea);
}
