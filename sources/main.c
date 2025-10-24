/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:23:40 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/10/24 16:54:44 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	parse_and_check(t_game *game, char *file)
{
	t_data	data;
	char	*line;
	int 	lines;
	int		fd;

	data_init(&data);
	fd = open(file, O_RDONLY);
	free_data(&data);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (!check_args(argc, argv))
		exit(EXIT_FAILURE);
	parse_and_check(&game, argv[1]);
	game.mlx = mlx_init(WIN_W, WIN_H, "cub3d", true);
	game.img = mlx_new_image(game.mlx, WIN_W, WIN_H);
	mlx_image_to_window(game.mlx, game.img, 0, 0);
	mlx_loop_hook(game.mlx, main_hook, &game);
	mlx_key_hook(game.mlx, key_hook, &game);
	mlx_loop(game.mlx);
	game_over(&game);
	mlx_delete_image(game.mlx, game.img);
	mlx_terminate(game.mlx);
	return (0);
}
