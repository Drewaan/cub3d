/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:23:40 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/12/10 16:40:23 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game		game;
	t_parser	parser;

	// Opción: ./cub3D map.cub --no-mlx
/* 	if (argc == 3 && strcmp(argv[2], "--no-mlx") == 0)
		disable_mlx = 1; */

	if (!check_args(argc, argv))
		return (1);
	(void)argc;
	parser_init(&parser);
	parse_file(&parser, argv[1]);
	data_to_game(&parser, &game);
	load_textures_from_parser(&game, &parser);

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
