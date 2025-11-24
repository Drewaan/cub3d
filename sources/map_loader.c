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

// map_loader.c
#include "cub3d.h"

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

void	load_map(t_data *d, char **ls)
{
	int	i;
	int	h;
	int	w;

	h = 0;
	while (ls[h])
		h++;
	d->map_h = h;
	w = get_max_width(ls);
	d->map_w = w;
	d->map = malloc(sizeof(char *) * (h + 1));
	i = 0;
	while (i < h)
	{
		d->map[i] = pad(ls[i], w);
		i++;
	}
	d->map[i] = NULL;
}