/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:09:01 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/12/10 16:57:59 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_ident(char *l)
{
	return (!ft_strncmp(l, "NO ", 3) || !ft_strncmp(l, "SO ", 3)
		|| !ft_strncmp(l, "WE ", 3) || !ft_strncmp(l, "EA ", 3)
		|| !ft_strncmp(l, "F ", 2) || !ft_strncmp(l, "C ", 2));
}

static int	is_empty_line(char *line)
{
	int	i;

	if (!line || !*line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && line[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

static int	is_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' 
		|| c == 'E' || c == 'W' || c == ' ' || c == '\t');
}

static int	is_map_line(char *line)
{
	int	i;
	int	has_wall;

	if (!line)
		return (0);

	i = 0;
	has_wall = 0;

	/* No permitir líneas que empiecen con espacio */
	if (line[0] == ' ' || line[0] == '\t')
		return (0);

	while (line[i] && line[i] != '\n')
	{
		if (!is_map_char(line[i]))
			return (0);
		if (line[i] == '1')
			has_wall = 1;
		i++;
	}
	return (has_wall);
}


static void	parse_ident_line(t_parser *p, char *l)
{
	char *tmp;

	if (!ft_strncmp(l, "NO ", 3))
	{
		if (p->paths.no)
			error_exit("Error: Duplicate NO texture");
		tmp = ft_strtrim(l + 3, " \t\n");
		p->paths.no = tmp ? tmp : ft_strdup(l + 3);
	}
	else if (!ft_strncmp(l, "SO ", 3))
	{
		if (p->paths.so)
			error_exit("Error: Duplicate SO texture");
		tmp = ft_strtrim(l + 3, " \t\n");
		p->paths.so = tmp ? tmp : ft_strdup(l + 3);
	}
	else if (!ft_strncmp(l, "WE ", 3))
	{
		if (p->paths.we)
			error_exit("Error: Duplicate WE texture");
		tmp = ft_strtrim(l + 3, " \t\n");
		p->paths.we = tmp ? tmp : ft_strdup(l + 3);
	}
	else if (!ft_strncmp(l, "EA ", 3))
	{
		if (p->paths.ea)
			error_exit("Error: Duplicate EA texture");
		tmp = ft_strtrim(l + 3, " \t\n");
		p->paths.ea = tmp ? tmp : ft_strdup(l + 3);
	}
	else if (!ft_strncmp(l, "F ", 2))
	{
		if (p->floor_color.red != -1)
			error_exit("Error: Duplicate floor color");
		parse_color(&p->floor_color, l + 2);
	}
	else if (!ft_strncmp(l, "C ", 2))
	{
		if (p->ceil_color.red != -1)
			error_exit("Error: Duplicate ceiling color");
		parse_color(&p->ceil_color, l + 2);
	}
}

static int	find_map_start(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (is_map_line(lines[i]))
			return (i);
		if (!is_ident(lines[i]) && !is_empty_line(lines[i]))
			error_exit("Error: Invalid line before map");
		i++;
	}
	error_exit("Error: No map found");
	return (-1);
}

static void	validate_map_block(char **lines, int start)
{
	int	i;
	int	found_empty;

	i = start;
	found_empty = 0;
	while (lines[i])
	{
		if (is_empty_line(lines[i]))
			found_empty = 1;
		else if (is_map_line(lines[i]))
		{
			if (found_empty)
				error_exit("Error: Duplicate map block");
		}
		else
			error_exit("Error: Invalid line inside map");
		i++;
	}
}


static void	check_all_textures(t_parser *p)
{
	if (!p->paths.no)
		error_exit("Error: Missing NO texture");
	if (!p->paths.so)
		error_exit("Error: Missing SO texture");
	if (!p->paths.we)
		error_exit("Error: Missing WE texture");
	if (!p->paths.ea)
		error_exit("Error: Missing EA texture");
	if (p->floor_color.red == -1)
		error_exit("Error: Missing floor color");
	if (p->ceil_color.red == -1)
		error_exit("Error: Missing ceiling color");
}

void	parse_file(t_parser *p, char *path)
{
	char	**lines;
	int		i;
	int		map_start;

	lines = read_file_to_array(path);
	i = 0;
	
	/* Parsear identificadores */
	while (lines[i] && !is_map_line(lines[i]))
	{
		if (is_ident(lines[i]))
			parse_ident_line(p, lines[i]);
		else if (!is_empty_line(lines[i]))
			error_exit("Error: Invalid identifier line");
		i++;
	}

	/* Verificar que todas las texturas estén */
	check_all_textures(p);

	/* Encontrar inicio del mapa */
	map_start = find_map_start(lines);
	
	/* Validar que el mapa sea un bloque continuo */
	validate_map_block(lines, map_start);

	/* Cargar el mapa */
	load_map_parser(p, lines + map_start);
	check_map_parser(p);
	free_split(lines);
}

static mlx_texture_t *load_png_strict(char *path)
{
	mlx_texture_t *t;

	if (!path)
		return (NULL);
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

	game->textures.floor_color = get_rgba(p->floor_color.red,
		p->floor_color.green, p->floor_color.blue, p->floor_color.alpha);
	game->textures.ceiling_color = get_rgba(p->ceil_color.red,
		p->ceil_color.green, p->ceil_color.blue, p->ceil_color.alpha);

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