/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:28:16 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/12/01 22:05:04 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/parser.h"

static void	check_digits(char **p)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (p[i][j])
	{
		if (!ft_isdigit(p[i][j]))
			error_exit("Invalid color digits");
		j++;
	}
}

void	parse_color(t_color *c, char *s)
{
	char	**p;
	int		rgb[3];

	p = ft_split(s, ',');
	if (!p)
		error_exit("Color split error");
	check_digits(p);
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
	free_split(p);
}
