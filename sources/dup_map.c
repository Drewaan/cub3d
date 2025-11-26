/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:36:57 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/11/24 19:37:10 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	**dup_map(t_map *map)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (map->map_h + 1));
	if (!copy)
		error_exit("Malloc failed");
	i = 0;
	while (i < map->map_h)
	{
		copy[i] = ft_strdup(map->map_array[i]);
		if (!copy[i])
			error_exit("Malloc failed");
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
