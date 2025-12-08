/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 19:36:47 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/12/08 18:50:07 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

mlx_texture_t *load_texture(char *path)
{
    if (!path)
        return (NULL);

    return mlx_load_png(path);
}

void get_wall_texture(t_game *g)
{
    t_raycast *r = &g->raycast;

    if (r->side == 0)
        g->wall_tex.tex = (r->raydir_x > 0) ? g->tex.east : g->tex.west;
    else
        g->wall_tex.tex = (r->raydir_y > 0) ? g->tex.south : g->tex.north;
}

t_color get_texture_pixel(mlx_texture_t *tex, int x, int y)
{
    t_color c;
    uint8_t *p;

    p = tex->pixels + ((y * tex->width + x) * 4);
    c.red   = p[0];
    c.green = p[1];
    c.blue  = p[2];
    c.alpha = p[3];
    return c;
}

void set_tex_params(t_wall_tex *wt, t_raycast *r)
{
    double wall_x;

    wall_x = r->wall_x - floor(r->wall_x);
    wt->tex_x = (int)(wall_x * wt->tex->width);

    if (r->side == 0 && r->raydir_x > 0)
        wt->tex_x = wt->tex->width - wt->tex_x - 1;
    if (r->side == 1 && r->raydir_y < 0)
        wt->tex_x = wt->tex->width - wt->tex_x - 1;
}
