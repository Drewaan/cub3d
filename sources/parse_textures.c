/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:11:44 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/12/08 16:07:46 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static mlx_texture_t	*load_tex(char *path)
{
	return (mlx_load_png(path));
}

int	parse_textures(t_game *game, char *line)
{
	char	**sp;

	sp = ft_split(line, ' ');
	if (!sp || !sp[1])
		return (1);
	if (!ft_strncmp(sp[0], "NO", 2))
		game->tex.north = load_tex(sp[1]);
	else if (!ft_strncmp(sp[0], "SO", 2))
		game->tex.south = load_tex(sp[1]);
	else if (!ft_strncmp(sp[0], "WE", 2))
		game->tex.west = load_tex(sp[1]);
	else if (!ft_strncmp(sp[0], "EA", 2))
		game->tex.east = load_tex(sp[1]);
	ft_free_split(sp);
	return (0);
}
