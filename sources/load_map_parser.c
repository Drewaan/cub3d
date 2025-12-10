/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:11:27 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/12/02 15:39:25 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	max_width(char **m)
{
	int	i = 0, max;
	int	len;

	i = 0, max = 0;
	while (m[i])
	{
		len = ft_strlen(m[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

static char	*pad(char *row, int w)
{
	int		len;
	char	*r;

	len = ft_strlen(row);
	r = malloc(w + 1);
	if (!r)
		error_exit("pad malloc");
	ft_memcpy(r, row, len);
	ft_memset(r + len, ' ', w - len);
	r[w] = '\0';
	return (r);
}

void	load_map_parser(t_parser *p, char **m)
{
	int	h;

	h = 0;
	while (m[h])
		h++;
	p->map_h = h;
	p->map_w = max_width(m);
	p->map = malloc(sizeof(char *) * (h + 1));
	if (!p->map)
		error_exit("map malloc");
	for (int i = 0; i < h; i++)
		p->map[i] = pad(m[i], p->map_w);
	p->map[h] = NULL;
}
