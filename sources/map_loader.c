/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:11:27 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/11/24 19:11:34 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	get_max_width(char **m)
{
	int	i;
	int	max;

	i = -1;
	max = 0;
	while (m[++i])
		if ((int)ft_strlen(m[i]) > max)
			max = ft_strlen(m[i]);
	return (max);
}

static char	*pad(char *row, int w)
{
	int		len;
	char	*r;

	len = ft_strlen(row);
	r = malloc(w + 1);
	if (!r)
		exit(1);
	ft_memcpy(r, row, len);
	ft_memset(r + len, ' ', w - len);
	r[w] = 0;
	return (r);
}

void	load_map(t_map *map, char **ls)
{
	int	i;
	int	h;
	int	w;

	h = 0;
	while (ls[h])
		h++;
	map->map_h = h;
	w = get_max_width(ls);
	map->map_w = w;
	map->map_array = malloc(sizeof(char *) * (h + 1));
	if (!map->map_array)
		error_exit("Malloc failed");
	i = 0;
	while (i < h)
	{
		map->map_array[i] = pad(ls[i], w);
		if (!map->map_array[i])
			error_exit("Malloc failed");
		i++;
	}
	map->map_array[i] = NULL;
}
