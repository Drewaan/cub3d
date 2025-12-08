/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 13:39:34 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/12/08 17:48:23 by vlorenzo         ###   ########.fr       */
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
