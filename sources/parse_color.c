/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:35:11 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/12/16 16:29:47 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	check_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			error_exit("Invalid color digits");
		i++;
	}
}

static int	count_parts(char **p)
{
	int	count;

	count = 0;
	while (p && p[count])
		count++;
	return (count);
}

void	parse_color(t_color *c, char *s)
{
	char	**p;
	int		rgb[3];

	p = ft_split(s, ',');
	if (!p || count_parts(p) != 3)
	{
		free_split(p);
		error_exit("Color format error: expected R,G,B");
	}
	gc_add(&g_game->gc, p, (void (*)(void *))free_split);
	if (!p[0][0] || !p[1][0] || !p[2][0])
		error_exit("Color format error: empty value");
	check_digits(p[0]);
	check_digits(p[1]);
	check_digits(p[2]);
	rgb[0] = ft_atoi(p[0]);
	rgb[1] = ft_atoi(p[1]);
	rgb[2] = ft_atoi(p[2]);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255 || rgb[2] < 0
		|| rgb[2] > 255)
		error_exit("Color out of range");
	c->red = rgb[0];
	c->green = rgb[1];
	c->blue = rgb[2];
	c->alpha = 255;
}
