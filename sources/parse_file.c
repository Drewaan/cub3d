/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:09:01 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/12/03 16:26:48 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_ident(char *l)
{
	return (!ft_strncmp(l, "NO ", 3) || !ft_strncmp(l, "SO ", 3)
		|| !ft_strncmp(l, "WE ", 3) || !ft_strncmp(l, "EA ", 3)
		|| !ft_strncmp(l, "F ", 2) || !ft_strncmp(l, "C ", 2));
}

static void	parse_ident_line(t_parser *p, char *l)
{
	char *tmp;

	if (!ft_strncmp(l, "NO ", 3))
	{
		tmp = ft_strtrim(l + 3, " \t\n");
		p->paths.no = tmp ? tmp : ft_strdup(l + 3);
	}
	else if (!ft_strncmp(l, "SO ", 3))
	{
		tmp = ft_strtrim(l + 3, " \t\n");
		p->paths.so = tmp ? tmp : ft_strdup(l + 3);
	}
	else if (!ft_strncmp(l, "WE ", 3))
	{
		tmp = ft_strtrim(l + 3, " \t\n");
		p->paths.we = tmp ? tmp : ft_strdup(l + 3);
	}
	else if (!ft_strncmp(l, "EA ", 3))
	{
		tmp = ft_strtrim(l + 3, " \t\n");
		p->paths.ea = tmp ? tmp : ft_strdup(l + 3);
	}
	else if (!ft_strncmp(l, "F ", 2))
		parse_color(&p->floor_color, l + 2);
	else if (!ft_strncmp(l, "C ", 2))
		parse_color(&p->ceil_color, l + 2);
}

void	parse_file(t_parser *p, char *path)
{
	char	**lines;
	int		i;

	lines = read_file_to_array(path);
	i = 0;
	while (lines[i] && is_ident(lines[i]))
	{
		parse_ident_line(p, lines[i]);
		i++;
	}
	load_map_parser(p, lines + i);
	check_map_parser(p);
	free_split(lines);
}

static mlx_texture_t *load_png_strict(char *path)
{
	mlx_texture_t *t;

	if (!path)
		return (NULL);
	/* comprobar acceso legible */
	if (access(path, R_OK) != 0)
	{
		fprintf(stderr, "Texture not accessible: %s\n", path);
		return (NULL);
	}
	t = mlx_load_png(path);
	if (!t)
		fprintf(stderr, "mlx_load_png failed for: %s\n", path);
	return (t);
}

void	load_textures_from_parser(t_game *game, t_parser *p)
{
	if (!game || !p)
		error_exit("load_textures_from_parser: invalid args");

	game->textures.north = load_png_strict(p->paths.no);
	game->textures.south = load_png_strict(p->paths.so);
	game->textures.west  = load_png_strict(p->paths.we);
	game->textures.east  = load_png_strict(p->paths.ea);

	/* convertir colores parser -> game (rgba int) */
	game->textures.floor_color = get_rgba(p->floor_color.red,
		p->floor_color.green, p->floor_color.blue, p->floor_color.alpha);
	game->textures.ceiling_color = get_rgba(p->ceil_color.red,
		p->ceil_color.green, p->ceil_color.blue, p->ceil_color.alpha);

	/* Si alguna textura no cargó, limpiamos las que sí y fallamos con mensaje */
	if (!game->textures.north || !game->textures.south
		|| !game->textures.west || !game->textures.east)
	{
		if (game->textures.north) mlx_delete_texture(game->textures.north);
		if (game->textures.south) mlx_delete_texture(game->textures.south);
		if (game->textures.west)  mlx_delete_texture(game->textures.west);
		if (game->textures.east)  mlx_delete_texture(game->textures.east);
		error_exit("One or more textures failed to load");
	}
}
