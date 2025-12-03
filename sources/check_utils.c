/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:40:44 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/12/02 19:46:11 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_args(int argc, char **argv)
{
	char	*tmp;
	int		fd;

	if (argc != 2)
	{
		ft_putendl_fd("Error: invalid arguments number", 2);
		return (0);
	}
	tmp = ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]));
	if (tmp == NULL)
	{
		ft_putendl_fd("Error: invalid map", 2);
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd("Error: invalid archive format", 2);
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

static int	is_valid(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ');
}

static void	locate_player(t_parser *p)
{
	for (int i = 0; i < p->map_h; i++)
		for (int j = 0; j < p->map_w; j++)
			if (ft_strchr("NSEW", p->map[i][j]))
			{
				p->player_x = i;
				p->player_y = j;
				p->player_dir = p->map[i][j];
				p->map[i][j] = '0';
			}
	if (p->player_x < 0)
		error_exit("Player missing");
}

static void	flood(char **m, int x, int y, t_parser *p)
{
	if (x < 0 || y < 0 || x >= p->map_h || y >= p->map_w)
		error_exit("Map open");
	if (m[x][y] == '1' || m[x][y] == 'V')
		return ;
	if (m[x][y] == ' ')
		error_exit("Space leak");
	m[x][y] = 'V';
	flood(m, x + 1, y, p);
	flood(m, x - 1, y, p);
	flood(m, x, y + 1, p);
	flood(m, x, y - 1, p);
}

void	check_map_parser(t_parser *p)
{
	char	**copy;

	locate_player(p);
	for (int i = 0; i < p->map_h; i++)
		for (int j = 0; j < p->map_w; j++)
			if (!is_valid(p->map[i][j]))
				error_exit("Invalid map character");
	copy = dup_map(p);
	flood(copy, p->player_x, p->player_y, p);
	free_split(copy);
}
