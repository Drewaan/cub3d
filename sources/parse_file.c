/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:09:01 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/12/10 18:46:06 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_map_line(char *line)
{
	int	i;
	int	has_wall;

	if (!line)
		return (0);
	i = 0;
	has_wall = 0;
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

int	find_map_start(char **lines)
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

void	validate_map_block(char **lines, int start)
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

void	check_all_textures(t_parser *p)
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
	while (lines[i] && !is_map_line(lines[i]))
	{
		if (is_ident(lines[i]))
			parse_ident_line(p, lines[i]);
		else if (!is_empty_line(lines[i]))
			error_exit("Error: Invalid identifier line");
		i++;
	}
	check_all_textures(p);
	map_start = find_map_start(lines);
	validate_map_block(lines, map_start);
	load_map_parser(p, lines + map_start);
	check_map_parser(p);
	free_split(lines);
}
