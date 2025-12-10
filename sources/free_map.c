/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:54:02 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/12/10 13:50:11 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_map(t_map *map)
{
	int	i;

	if (!map || !map->map_array)
		return;
	i = 0;
	while (map->map_array[i])
	{
		free(map->map_array[i]);
		i++;
	}
	free(map->map_array);
	map->map_array = NULL;
}
