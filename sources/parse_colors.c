/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:35:11 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/12/08 16:07:59 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	to_color(char *s)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(s, ',');
	if (!rgb || !rgb[2])
		return (-1);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	ft_free_split(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return ((r << 24) | (g << 16) | (b << 8) | 255);
}

int	parse_colors(t_game *game, char *line)
{
	char	**sp;
	int		color;

	sp = ft_split(line, ' ');
	if (!sp || !sp[1])
		return (1);
	color = to_color(sp[1]);
	if (color < 0)
		return (1);
	if (!ft_strncmp(sp[0], "F", 1))
		game->tex.floor_color = color;
	else
		game->tex.ceil_color = color;
	ft_free_split(sp);
	return (0);
}
