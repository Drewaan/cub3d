/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:40:44 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/12/10 16:39:08 by aamaya-g         ###   ########.fr       */
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
	if (tmp == NULL || ft_strcmp(tmp, ".cub") != 0)
	{
		ft_putendl_fd("Error: invalid map extension", 2);
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd("Error: cannot open file", 2);
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
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (i < p->map_h)
	{
		j = 0;
		while (j < p->map_w)
		{
			if (ft_strchr("NSEW", p->map[i][j]))
			{
				player_count++;
				if (player_count > 1)
					error_exit("Error: Duplicate player position");
				p->player_x = i;
				p->player_y = j;
				p->player_dir = p->map[i][j];
				p->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	if (player_count == 0)
		error_exit("Error: No player found");
}

static void	flood(char **m, int x, int y, t_parser *p)
{
	if (x < 0 || y < 0 || x >= p->map_h || y >= p->map_w)
		error_exit("Error: Map not closed");
	if (m[x][y] == '1' || m[x][y] == 'V')
		return ;
	if (m[x][y] == ' ')
		error_exit("Error: Map not closed (space leak)");
	m[x][y] = 'V';
	flood(m, x + 1, y, p);
	flood(m, x - 1, y, p);
	flood(m, x, y + 1, p);
	flood(m, x, y - 1, p);
}

static void	check_borders(t_parser *p)
{
	int	i;
	int	j;

	/* Verificar primera y última fila */
	i = 0;
	while (i < p->map_w)
	{
		if (p->map[0][i] != '1' && p->map[0][i] != ' ')
			error_exit("Error: Map not closed (top border)");
		if (p->map[p->map_h - 1][i] != '1' && p->map[p->map_h - 1][i] != ' ')
			error_exit("Error: Map not closed (bottom border)");
		i++;
	}

	/* Verificar primera y última columna */
	j = 0;
	while (j < p->map_h)
	{
		if (p->map[j][0] != '1' && p->map[j][0] != ' ')
			error_exit("Error: Map not closed (left border)");
		if (p->map[j][p->map_w - 1] != '1' && p->map[j][p->map_w - 1] != ' ')
			error_exit("Error: Map not closed (right border)");
		j++;
	}
}

void	check_map_parser(t_parser *p)
{
	char	**copy;
	int		i;
	int		j;

	/* Verificar caracteres válidos */
	i = 0;
	while (i < p->map_h)
	{
		j = 0;
		while (j < p->map_w)
		{
			if (!is_valid(p->map[i][j]))
				error_exit("Error: Invalid character in map");
			j++;
		}
		i++;
	}

	/* Localizar jugador y verificar que sea único */
	locate_player(p);

	/* Verificar bordes */
	check_borders(p);

	/* Flood fill para verificar cierre */
	copy = dup_map(p);
	flood(copy, p->player_x, p->player_y, p);
	free_split(copy);
}