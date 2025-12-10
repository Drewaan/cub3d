/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:23:40 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/12/10 13:49:39 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	setup(t_game *game, const char *file)
{
	init_game(game);

	if (parse_cub(game, file))
		return (ft_printf("Error: parsing fallido\n"), 1);

	if (validate_all_textures(game))
		return (1);

	init_player(game);

	game->mlx = mlx_init(WIN_W, WIN_H, "cub3D", true);
	if (!game->mlx)
		return (ft_printf("Error: mlx_init falló\n"), 1);

	game->img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	if (!game->img)
		return (ft_printf("Error: mlx_new_image falló\n"), 1);

	mlx_image_to_window(game->mlx, game->img, 0, 0);
	mlx_key_hook(game->mlx, key_hook, game);
	mlx_loop_hook(game->mlx, main_hook, game);

	return (0);
}

int	main(int argc, char **argv)
{
	t_game		game;
	t_parser	parser;

	// Opción: ./cub3D map.cub --no-mlx
/* 	if (argc == 3 && strcmp(argv[2], "--no-mlx") == 0)
		disable_mlx = 1; */

	if (argc != 2)
		return (ft_printf("Uso: ./cub3D <map.cub>\n"), 1);

	if (setup(&game, argv[1]))
	{
		cleanup_game(&game);
		return (1);
	}

	mlx_loop(game.mlx);

	cleanup_game(&game);

	if (game.img)
		mlx_delete_image(game.mlx, game.img);

	mlx_terminate(game.mlx);
	return (0);
}
