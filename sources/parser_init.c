/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:27:58 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/12/01 20:06:38 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/parser.h"

void	parser_init(t_parser *p)
{
	p->paths.no = NULL;
	p->paths.so = NULL;
	p->paths.we = NULL;
	p->paths.ea = NULL;
	p->floor_color.red = -1;
	p->floor_color.green = -1;
	p->floor_color.blue = -1;
	p->floor_color.alpha = 255;
	p->ceil_color = p->floor_color;
	p->map = NULL;
	p->map_h = 0;
	p->map_w = 0;
	p->player_x = -1;
	p->player_y = -1;
	p->player_dir = 0;
	p->dir_x = 0;
	p->dir_y = 0;
	p->plane_x = 0;
	p->plane_y = 0;
}
