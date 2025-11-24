/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:09:01 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/11/24 19:30:44 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// parser.c
#include "../includes/cub3d.h"

static int	is_ident(char *l)
{
	return (!ft_strncmp(l, "NO ", 3) || !ft_strncmp(l, "SO ", 3)
		|| !ft_strncmp(l, "WE ", 3) || !ft_strncmp(l, "EA ", 3)
		|| !ft_strncmp(l, "F ", 2) || !ft_strncmp(l, "C ", 2));
}

static void	parse_ident_line(t_data *d, char *l)
{
	if (!ft_strncmp(l, "NO ", 3))
		d->paths.no = ft_strdup(l + 3);
	else if (!ft_strncmp(l, "SO ", 3))
		d->paths.so = ft_strdup(l + 3);
	else if (!ft_strncmp(l, "WE ", 3))
		d->paths.we = ft_strdup(l + 3);
	else if (!ft_strncmp(l, "EA ", 3))
		d->paths.ea = ft_strdup(l + 3);
	else if (!ft_strncmp(l, "F ", 2))
		parse_color(&d->floor_color, l + 2);
	else if (!ft_strncmp(l, "C ", 2))
		parse_color(&d->ceil_color, l + 2);
}

static int	find_map_start(char **ls)
{
	int	i;

	i = 0;
	while (ls[i])
	{
		if (!is_ident(ls[i]) && ft_strlen(ls[i]) > 0)
			return (i);
		i++;
	}
	error_exit("No map found");
	return (-1);
}

void	parse_file(t_data *d, char *path)
{
	char	**ls;
	int		i;
	int		m;

	check_file_extension(path);
	ls = read_file_to_array(path);
	i = 0;
	while (ls[i] && is_ident(ls[i]))
	{
		parse_ident_line(d, ls[i]);
		i++;
	}
	m = find_map_start(ls);
	load_map(d, ls + m);
	check_identifiers(d);
	free_split(ls);
}
