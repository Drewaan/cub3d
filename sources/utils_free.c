/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:49:01 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/12/08 22:22:06 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void free_textures(t_game *g)
{
    if (g->tex.north)
        mlx_delete_texture(g->tex.north);
    if (g->tex.south)
        mlx_delete_texture(g->tex.south);
    if (g->tex.east)
        mlx_delete_texture(g->tex.east);
    if (g->tex.west)
        mlx_delete_texture(g->tex.west);

    g->tex.north = NULL;
    g->tex.south = NULL;
    g->tex.east = NULL;
    g->tex.west = NULL;
}

void	cleanup_game(t_game *g)
{
	free_map(&g->map);
	free_textures(g);
	if (g->img)
		mlx_delete_image(g->mlx, g->img);
	if (g->mlx)
		mlx_terminate(g->mlx);
}

void	ft_free_split(char **arr)
{
	int	i;

	if (!arr)
		return;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
