/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:54:02 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/12/10 19:59:54 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_parser(t_parser *p)
{
	if (p->paths.no)
		free(p->paths.no);
	if (p->paths.so)
		free(p->paths.so);
	if (p->paths.we)
		free(p->paths.we);
	if (p->paths.ea)
		free(p->paths.ea);
	free_split(p->map);
}

void	error_exit(char *msg)
{
	ft_putendl_fd("Error", 2);
	if (msg)
		ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	game_over(t_game *g)
{
	if (!g)
		return ;
	if (g->map.map_array)
		free_split(g->map.map_array);
	if (g->img)
		mlx_delete_image(g->mlx, g->img);
	if (g->textures.north)
		mlx_delete_texture(g->textures.north);
	if (g->textures.south)
		mlx_delete_texture(g->textures.south);
	if (g->textures.west)
		mlx_delete_texture(g->textures.west);
	if (g->textures.east)
		mlx_delete_texture(g->textures.east);
	if (g->mlx)
		mlx_terminate(g->mlx);
}
