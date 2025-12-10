/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:11:27 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/12/10 18:44:59 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	max_width(char **m)
{
	int	i;
	int	max;
	int	len;

	i = 0;
	max = 0;
	while (m[i] && !is_empty_line(m[i]))
	{
		len = ft_strlen(m[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

char	*pad(char *row, int w)
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

int	count_map_lines(char **m)
{
	int	count;

	count = 0;
	while (m[count] && !is_empty_line(m[count]))
		count++;
	if (count == 0)
		error_exit("Error: Empty map");
	return (count);
}

void	load_map_parser(t_parser *p, char **m)
{
	int	h;
	int	i;

	if (!m || !m[0])
		error_exit("Error: No map data");
	h = count_map_lines(m);
	p->map_h = h;
	p->map_w = max_width(m);
	if (p->map_h < 3 || p->map_w < 3)
		error_exit("Error: Map too small");
	p->map = malloc(sizeof(char *) * (h + 1));
	if (!p->map)
		error_exit("map malloc");
	i = 0;
	while (i < h)
	{
		p->map[i] = pad(m[i], p->map_w);
		i++;
	}
	p->map[h] = NULL;
}
