/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:23:40 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/12/08 17:24:43 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	setup(t_game *game, const char *file)
{
	init_game(game);

	if (!check_cub_extension(file))
		return (1);
	if (parse_cub(game, file))
		return (1);

	init_player(game);

	game->mlx = mlx_init(WIN_W, WIN_H, "cub3D", true);
	if (!game->mlx)
		return (1);

	/* Aquí la imagen PRINCIPAL que usa raycast & draw */
	game->img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	if (!game->img)
		return (1);

	mlx_image_to_window(game->mlx, game->img, 0, 0);

	/* Hooks */
	mlx_key_hook(game->mlx, key_hook, game);
	mlx_loop_hook(game->mlx, main_hook, game);

	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (1);

	if (setup(&game, argv[1]))
		return (1);

	mlx_loop(game.mlx);

	/* Liberaciones */
	free_map(&game.map);

	if (game.img)
		mlx_delete_image(game.mlx, game.img);

	mlx_terminate(game.mlx);
	return (0);
}
