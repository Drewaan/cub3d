/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 19:36:47 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/12/08 20:42:32 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

mlx_texture_t	*load_texture(char *path)
{
	mlx_texture_t	*tex;

	if (!path)
	{
		ft_printf("Error: Path not found\n");
		return (NULL);
	}
	tex = mlx_load_png(path);
	if (!tex)
    {
        ft_printf("Error: Texture not loaded: %s\n", path);
        return (NULL);
    }
	return (tex);
}

void	get_wall_texture(t_game *g)
{
	t_raycast	*r;

	r = &g->raycast;
	if (r->side == 0)
	{
		if (r->raydir_x > 0)
			g->wall_tex.tex = g->tex.east;
		else
			g->wall_tex.tex = g->tex.west;
	}
	else
	{
		if (r->raydir_y > 0)
			g->wall_tex.tex = g->tex.south;
		else
			g->wall_tex.tex = g->tex.north;
	}
}

t_color	get_texture_pixel(mlx_texture_t *tex, int x, int y)
{
	t_color		color;
	uint8_t		*p;

	p = tex->pixels + ((y * tex->width + x) * 4);
	color.red = p[0];
	color.green = p[1];
	color.blue = p[2];
	color.alpha = p[3];
	return (color);
}

void	set_tex_params(t_wall_tex *wt, t_raycast *r)
{
	double	wall_x;

	wall_x = r->wall_x;
	if (wall_x < 0.0)
		wall_x = 0.0;
	if (wall_x > 1.0)
		wall_x = 1.0;

	wt->tex_x = (int)(wall_x * wt->tex->width);
	if (r->side == 0 && r->raydir_x > 0)
		wt->tex_x = wt->tex->width - wt->tex_x - 1;
	if (r->side == 1 && r->raydir_y < 0)
		wt->tex_x = wt->tex->width - wt->tex_x - 1;
}
