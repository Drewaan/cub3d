/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:11:44 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/12/08 22:19:24 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static mlx_texture_t	*load_tex(char *path)
{
	if (!path)
		return (NULL);

	mlx_texture_t *tex = mlx_load_png(path);
	if (!tex)
		ft_printf("Error: no se pudo cargar textura: %s\n", path);
	return (tex);
}

int	parse_textures(t_game *g, char *line)
{
	char	**sp;

	sp = ft_split(line, ' ');
	if (!sp || !sp[1])
		return (ft_free_split(sp), 1);

	if (!ft_strncmp(sp[0], "NO", 2))
		g->tex.north = load_tex(sp[1]);
	else if (!ft_strncmp(sp[0], "SO", 2))
		g->tex.south = load_tex(sp[1]);
	else if (!ft_strncmp(sp[0], "WE", 2))
		g->tex.west = load_tex(sp[1]);
	else if (!ft_strncmp(sp[0], "EA", 2))
		g->tex.east = load_tex(sp[1]);

	ft_free_split(sp);
	return (0);
}

int	validate_all_textures(t_game *g)
{
	if (!g->tex.north || !g->tex.south || !g->tex.east || !g->tex.west)
	{
		ft_printf("Error: faltan texturas\n");
		free_textures(g);
		return (1);
	}
	return (0);
}