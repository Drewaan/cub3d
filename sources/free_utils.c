/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:54:02 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/10/24 15:57:10 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	game_over(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.map_h)
	{
		free(game->map.map_array[i]);
		i++;
	}
	free(game->map.map_array);
	mlx_delete_texture(game->textures.north);
	mlx_delete_texture(game->textures.south);
	mlx_delete_texture(game->textures.west);
	mlx_delete_texture(game->textures.east);
}

void	free_data(t_data *data)
{
	free(data->north);
	free(data->south);
	free(data->east);
	free(data->west);
}
