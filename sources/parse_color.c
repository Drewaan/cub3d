/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:35:11 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/11/24 19:35:17 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	check_digits(char **p)
{
	if (!p[0] || !p[1] || !p[2])
		error_exit("Invalid color format");
	if (!ft_str_isdigit(p[0]) || !ft_str_isdigit(p[1]) || !ft_str_isdigit(p[2]))
		error_exit("Invalid color digits");
}

void	parse_color(t_color *c, char *s)
{
	char	**p;
	int		i;
	int		val;

	p = ft_split(s, ',');
	if (!p)
		error_exit("Color split error");
	check_digits(p);
	i = 0;
	while (i < 3)
	{
		val = ft_atoi(p[i]);
		if (val < 0 || val > 255)
			error_exit("Color out of range");
		if (i == 0)
			c->red = val;
		else if (i == 1)
			c->green = val;
		else if (i == 2)
			c->blue = val;
		i++;
	}
	c->alpha = 255;
	free_split(p);
}
