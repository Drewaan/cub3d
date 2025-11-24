/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:12:55 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/11/24 19:12:59 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// check_map.c
#include "cub3d.h"

static int	valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W');
}

static void	locate_player(t_data *d)
{
	int	i;
	int	j;

	d->player_count = 0;
	i = -1;
	while (d->map[++i])
	{
		j = -1;
		while (d->map[i][++j])
			if (ft_strchr("NSEW", d->map[i][j]))
			{
				d->player_x = i;
				d->player_y = j;
				d->player_dir = d->map[i][j];
				d->player_count++;
				d->map[i][j] = '0';
			}
	}
	if (d->player_count != 1)
		error_exit("Invalid player count");
}

static void	flood(char **m, int x, int y, t_data *d)
{
	if (x < 0 || y < 0 || x >= d->map_h || y >= d->map_w)
		error_exit("Map not closed");
	if (m[x][y] == '1' || m[x][y] == 'V')
		return ;
	if (m[x][y] == ' ')
		error_exit("Space leak");
	m[x][y] = 'V';
	flood(m, x + 1, y, d);
	flood(m, x - 1, y, d);
	flood(m, x, y + 1, d);
	flood(m, x, y - 1, d);
}

void	check_map(t_data *d)
{
	int		i;
	int		j;
	char	**copy;

	locate_player(d);
	i = -1;
	while (d->map[++i])
	{
		j = -1;
		while (d->map[i][++j])
			if (!valid_char(d->map[i][j]) && d->map[i][j] != ' ')
				error_exit("Invalid map char");
	}
	copy = dup_map(d);
	flood(copy, d->player_x, d->player_y, d);
	free_map(copy);
}