/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:09:01 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/12/02 15:41:33 by aamaya-g         ###   ########.fr       */
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
	if (!ft_strncmp(l, "NO ", 3))
		p->paths.no = ft_strdup(l + 3);
	else if (!ft_strncmp(l, "SO ", 3))
		p->paths.so = ft_strdup(l + 3);
	else if (!ft_strncmp(l, "WE ", 3))
		p->paths.we = ft_strdup(l + 3);
	else if (!ft_strncmp(l, "EA ", 3))
		p->paths.ea = ft_strdup(l + 3);
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
