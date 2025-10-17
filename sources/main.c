/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:23:40 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/10/17 16:44:59 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;
	if (!check_args(argc, argv))
		exit(EXIT_FAILURE);
	game.mlx = mlx_init(WIN_W, WIN_H, "cub3d", true);
	game.img = mlx_new_image(game.mlx, WIN_W, WIN_H);
	
	return (0);
}
