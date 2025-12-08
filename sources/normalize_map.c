/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:06:16 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/12/08 17:39:03 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	normalize_map(t_map *map)
{
	int		y;
	int		len;
	char	*new;

	y = 0;
	while (y < map->height)
	{
		len = ft_strlen(map->map_array[y]);
		if (len < map->width)
		{
			new = malloc(map->width + 1);
			if (!new)
				return ;

			ft_memset(new, ' ', map->width);
			new[map->width] = '\0';

			ft_memcpy(new, map->map_array[y], len);

			free(map->map_array[y]);
			map->map_array[y] = new;
		}
		y++;
	}
}
