/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:30:09 by vlorenzo          #+#    #+#             */
/*   Updated: 2025/12/01 20:20:25 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/parser.h"

int	main(int argc, char **argv)
{
	t_game		game;
	t_parser	parser;

	if (!check_args(argc, argv))
		return (1);
	parser_init(&parser);
	parse_file(&parser, argv[1]);
	check_map_parser(&parser);
	data_to_game(&parser, &game);
	game.player.speed = 0.20;
	game.player.rotate_speed = 0.08;
	game.mlx = mlx_init(WIN_W, WIN_H, "cub3D", false);
	if (!game.mlx)
		error_exit("MLX init failed");
	game.img = mlx_new_image(game.mlx, WIN_W, WIN_H);
	mlx_image_to_window(game.mlx, game.img, 0, 0);
	mlx_loop_hook(game.mlx, main_hook, &game);
	mlx_key_hook(game.mlx, key_hook, &game);
	mlx_loop(game.mlx);
	free_parser(&parser);
	game_over(&game);
	return (0);
}
