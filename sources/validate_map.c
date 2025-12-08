/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 13:56:10 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/12/08 18:06:01 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	invalid(char c)
{
	return (!(c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W' || c == ' '));
}

int	validate_map(t_map *map)
{
	int	x;
	int	y;

	if (!map || !map->map_array)
		return (1);

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (invalid(map->map_array[y][x]))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}
